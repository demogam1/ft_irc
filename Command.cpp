/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:07:42 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 15:31:47 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Command.hpp"

Command::Command(std::string const & password, std::list<Client> & clients, std::string const & IP) : password(password), clients(clients), IP(IP) 
{
	cmdMap[std::string("NICK")] = &Command::nick;
	cmdMap[std::string("USER")] = &Command::user; 
	cmdMap[std::string("PASS")] = &Command::pass; 
	cmdMap[std::string("QUIT")] = &Command::quit;
	cmdMap[std::string("OPER")] = &Command::oper;
	cmdMap[std::string("MODE")] = &Command::mode;
	cmdMap[std::string("JOIN")] = &Command::join;
	cmdMap[std::string("PART")] = &Command::part;
	cmdMap[std::string("PING")] = &Command::pong;
	cmdMap[std::string("KILL")] = &Command::kill;
	cmdMap[std::string("PRIVMSG")] = &Command::privatmsg;
}

Command::~Command() {}

void	Command::sendMsg(Client const & client, std::string nb, std::string opt, std::string msg)
{
	std::string	message(":" + IP);
	if (!opt.empty())
		message += " " + nb + " " + client.getNick() + " " + opt + " " + msg + "\r\n";
	else
		message += " " + nb + " " + client.getNick() + " " + msg + "\r\n";
	send(client.getSocket(), message.c_str(), message.length(), 0);
}

void    Command::sendConfirm(Client const & client, std::string const & cmd, std::string const & opt)
{
	std::string message(":" + CLIENT);
	if (opt.empty())
		message += " " + cmd + "\r\n";
	else
		message += " " + cmd + " :" + opt + "\r\n";
	send(client.getSocket(), message.c_str(), message.length(), 0);
}

void    Command::sendConfirmTo(Client const & client, Client const & terminator, std::string const & cmd, std::string const & opt)
{
	std::string message(":" + TERMINATOR);
	if (opt.empty())
		message += " " + cmd + "\r\n";
	else
		message += " " + cmd + " :" + opt + "\r\n";
	send(client.getSocket(), message.c_str(), message.length(), 0);
}

void    Command::sendError(Client const & client, std::string const & arg, std::string const & opt)
{
	std::string message("ERROR");
	message += " :" + arg + ": " + opt + "\r\n";
	send(client.getSocket(), message.c_str(), message.length(), 0);
}

void    Command::sendSpecConfirm(Client const & client,std::string const & prefix, std::string const & cmd, std::string const & opt)
{
	std::string message(":" + prefix);
	message += " " + cmd + " " + prefix + " :" + opt + "\r\n";
	send(client.getSocket(), message.c_str(), message.length(), 0);
}

bool	Command::isSpecial(char c) const
{
	if (c == '[' || c == ']' || c ==  '\\' || c == '`' || c ==  '_'
			|| c ==  '^' || c ==  '{' || c ==  '|' || c ==  '}')
		return (true);
	return (false);
}

void	Command::setIP(std::string const & val) { IP = val;}

std::vector<std::string>	Command::splitCmd(std::string const & s, std::string const & seperator)
{
	 	std::vector<std::string> output;
 		std::string::size_type prev_pos = 0, pos = 0;
 		while((pos = s.find(seperator, pos)) != std::string::npos)
 		{
	 		if (s[prev_pos] == ':' && prev_pos != 0)
 			{
	 			std::string substring( s.substr(prev_pos) );
 				output.push_back(substring);
 				return (output);
 			}
 			std::string substring( s.substr(prev_pos, pos-prev_pos) );
 			if (!substring.empty())
 				output.push_back(substring);
 			pos += seperator.length();
 			prev_pos = pos;
 		}
 		std::string substring( s.substr(prev_pos, pos-prev_pos) );
 		if (!substring.empty())
	 		output.push_back(substring);
	 return output;
}

void	Command::parsCmd(Client & client)
{
	(void)clients;
	std::vector<std::string>	cmd;
	if(client.getBuff()[client.getBuff().length() - 2] == '\r')
		cmd = splitCmd(client.getBuff(), "\r\n");
	else
		cmd = splitCmd(client.getBuff(), "\n");
	std::vector<std::string>::iterator	it = cmd.begin();
	std::map<std::string, pfunc>::iterator	iter;
	for (; it != cmd.end(); it++)
	{
		std::vector<std::string>	cmds = splitCmd(*it, " ");
		if (cmds[0][0] == ':')
		{
			cmds[0].erase(0, 1);
			if (cmds[0] != client.getNick())
				return ;
			cmds.erase(cmds.begin());
		}
		std::string	tmp(cmds[0]);
		std::transform(cmds[0].begin(), cmds[0].end(),cmds[0].begin(), toupper);
		iter = cmdMap.find(cmds[0]);
		if (iter != cmdMap.end())
			CALL_MEMBER_FN(*this, iter->second) (cmds, client);
		else if (client.getRegistered())
			sendMsg(client, "421", tmp, ERR_UNKNOWNCOMMAND);
	}
}

void	Command::registerClient(Client & client)
{
	if (client.getNicked() && client.getUsered())
	{
		if (!password.empty() && client.getPass() != password)
		{
			sendMsg(client, "464", "", ERR_PASSWDMISMATCH);
			return ;
		}
		client.setRegistered(true);
		sendMsg(client, "001", "", RPL_WELCOME); 
	}
}
