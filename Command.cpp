/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:07:42 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/19 10:24:29 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(std::string const & password, std::list<Client> & clients, std::string const & IP) : password(password), clients(clients), IP(IP) 
{
	cmdMap[std::string("NICK")] = &Command::nick; 
	cmdMap[std::string("USER")] = &Command::user; 
	cmdMap[std::string("PASS")] = &Command::pass; 
	cmdMap[std::string("QUIT")] = &Command::quit;
	cmdMap[std::string("QUIT")] = &Command::quit;

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

void	Command::sendConfirm(Client const & client, std::vector<std::string> const & cmds)
{
	std::string message(":" + CLIENT);
	message += " " + cmds[0] + " :" + cmds[1] + "\r\n";
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

void	Command::parsCmd(Client & client)
{
	(void)clients;
	std::vector<std::string>	cmd;
	if(client.getBuff()[client.getBuff().length() - 2] == '\r')
		cmd = split(client.getBuff(), "\r\n");
	else
		cmd = split(client.getBuff(), "\n");
	std::vector<std::string>::iterator	it = cmd.begin();
	std::map<std::string, pfunc>::iterator	iter;
	for (; it != cmd.end(); it++)
	{
		std::vector<std::string>	cmds = split(*it, " ");
		if (cmds[0][0] == ':')
		{
			cmds[0].erase(0, 1);
			if (cmds[0] != client.getNick())
				return ;
			cmds.erase(cmds.begin());
		}
		std::transform(cmds[0].begin(), cmds[0].end(),cmds[0].begin(), toupper);
		iter = cmdMap.find(cmds[0]);
		if (iter != cmdMap.end())
			CALL_MEMBER_FN(*this, iter->second) (cmds, client);
		else if (client.getRegistered())
			sendMsg(client, "421", cmds[0], ERR_UNKNOWNCOMMAND);
	}
}

void	Command::registerClient(Client & client)
{
	if (client.getNicked() && client.getUsered())
	{
		if (client.getPass() != password)
		{
			sendMsg(client, "464", "", ERR_PASSWDMISMATCH);
			return ;
		}
		client.setRegistered(true);
		sendMsg(client, "001", "", RPL_WELCOME); 
	}
}

void	Command::pass(std::vector<std::string> cmds, Client & client)
{
	if (cmds.size() == 1)
	{
		sendMsg(client, "431", "", ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (client.getRegistered())
	{
		sendMsg(client, "462", "", ERR_ALREADYREGISTRED);
		return;
	}
	client.setPass(cmds[1]);
}

void	Command::nick(std::vector<std::string> cmds, Client & client)
{
	(void)client;
	if (cmds.size() == 1)
	{
		sendMsg(client, "431", "", ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (cmds[1].length() > 8)
		cmds[1].resize(9);
	std::list<Client>::iterator	it = clients.begin();
	for(; it != clients.end(); it++)
		if (cmds[1] == it->getNick() && &(*it) != &client)
		{
			sendMsg(client, "433", cmds[1], ERR_NICKNAMEINUSE);
			return ;
		}
	if ((!isalpha(cmds[1][0]) && !isSpecial(cmds[1][0])))
	{
		sendMsg(client, "432", cmds[1], ERR_ERRONEUSNICKNAME);
		return;
	}
	for (size_t i = 1; i < cmds[1].length(); i++)
	{
		if (!isalpha(cmds[1][i]) && !isSpecial(cmds[1][i]) && !isdigit(cmds[1][i]))
		{
			sendMsg(client, "432", cmds[1], ERR_ERRONEUSNICKNAME);
			return;
		}
	}
	if (client.getNick() != cmds[1])
	{
		if (client.getRegistered())
			sendConfirm(client, cmds);
		client.setNick(cmds[1]);
		if (!client.getRegistered())
		{
			client.setNicked(true);
			registerClient(client);
		}
	}
}

void	Command::user(std::vector<std::string> cmds, Client & client)
{
	if (client.getRegistered())
	{
		sendMsg(client, "462", "", ERR_ALREADYREGISTRED);
		return;
	}
	if (cmds.size() <= 4 || cmds[4] == ":")
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return;
	}
	client.setUser(cmds[1]);
	client.setMode(cmds[2]);
	client.setUnused(cmds[3]);
	if (cmds[4][0] == ':')
		cmds[4].erase(0, 1);
	client.setRealname(cmds[4]);
	client.setUsered(true);
	registerClient(client);
}

void	Command::quit(std::vector<std::string> cmds, Client & client)
{
	(void)cmds;
	(void)client;
}
