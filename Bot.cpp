/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:01:30 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/03 17:36:42y asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot() : port(4242), pass(""), IP("127.0.0.1"), sock(0), isRegistered(0) { command(); }

Bot::Bot(int port, std::string const & pass, std::string const & IP) : port(port), pass(pass), IP(IP), sock(0), isRegistered(0) { command(); }

Bot::~Bot() { close(client_fd); }

void	Bot::command()
{
	cmdMap[std::string("PING")] = &Bot::pong; 
	cmdMap[std::string("INVITE")] = &Bot::invite; 
	cmdMap[std::string("PRIVMSG")] = &Bot::privmsg; 
	cmdBotMap[std::string("HELLO")] = &Bot::hello; 
	cmdBotMap[std::string("TIME")] = &Bot::timeCmd; 
}

void	Bot::pong(std::vector<std::string> cmds)
{
	std::string	message("PONG " + cmds[1] + "\r\n");
	send(sock, message.c_str(), message.length(), 0);
}

void	Bot::invite(std::vector<std::string> cmds)
{
	if (cmds[3][0] == ':')
		cmds[3].erase(0, 1);
	std::string	message("JOIN " + cmds[3] + "\r\n");
	
	send(sock, message.c_str(), message.length(), 0);
}

void	Bot::privmsg(std::vector<std::string> cmds)
{
	if (cmds[0][0] == ':')
		cmds[0].erase(0, 1);
	if (cmds[3][0] == ':')
		cmds[3].erase(0, 1);
	if (cmds[2][0] == '#')
		cmds[0].assign(cmds[2]);
	else
		cmds[0] = cmds[0].substr(0, cmds[0].find("!"));
	std::vector<std::string>	botCmds = ft_split(cmds[3], " ");
	std::transform(botCmds[0].begin(), botCmds[0].end(), botCmds[0].begin(), toupper);
	if (botCmds[0] != "!BOT")
		return ;
	std::transform(botCmds[1].begin(), botCmds[1].end(), botCmds[1].begin(), toupper);
	std::map<std::string, pfunc>::iterator	itMap;
	itMap = cmdBotMap.find(botCmds[1]);
	if (itMap != cmdBotMap.end())
		CALL_MEMBER_FN(*this, itMap->second) (cmds);
}

void	Bot::timeCmd(std::vector<std::string> cmds)
{
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	std::string	message("PRIVMSG " + cmds[0] + " :Current Date Time : " + buf + "\r\n");
	send(sock, message.c_str(), message.length(), 0);
}

void	Bot::hello(std::vector<std::string> cmds)
{
	std::string	message("PRIVMSG " + cmds[0] + " :Hello, I am a AutoBot!\r\n");
	send(sock, message.c_str(), message.length(), 0);
}

void	Bot::init()
{
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Socket creation error");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	
	if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0)
	{
		struct hostent	*host_entry;
		host_entry = gethostbyname(IP.c_str());
		IP = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
		if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0)
			throw std::runtime_error("Invalid address / Address not supported");
	}
	
	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
		throw std::runtime_error("Connection Failed");
} 

void	Bot::run()
{
	char buffer[1024] = {0};
	int valread;
	std::string	botRegister;

	if (!pass.empty())
		botRegister += "PASS " + pass + "\r\n";
	
	botRegister += "NICK autoBot\r\nUSER autoBot bot * :Auto Bot\r\n";

	send(sock, botRegister.c_str(), botRegister.length(), 0);
	
	while((valread = recv(sock, buffer, 1024, 0)))
	{
		buffer[valread] = '\0';
		buff.append(buffer);
		if (buff[buff.length() - 1] == '\n')
		{
			cmdPars(buff);
			buff.clear();
		}
		bzero(buffer, valread);
	}
	std::cout << YELLOW + "Connection lost" + RESET << std::endl;
}

std::vector<std::string>	Bot::splitCmd(std::string const & s, std::string const & seperator)
{
	 	std::vector<std::string> output;
		std::string::size_type prev_pos = 0, pos = 0;
		size_t i = 0;
		bool	point;
		for (; i < s.length(); i++)
			if (s[i] != ' ')
				break;
		if (s[i] == ':')
			point = false;
		else
			point = true;
			
 		while((pos = s.find(seperator, pos)) != std::string::npos)
 		{
	 		if (s[prev_pos] == ':')
 			{
				if (point)
				{
	 				std::string substring( s.substr(prev_pos) );
 					output.push_back(substring);
 					return (output);
				}
				else
					point = true;
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

std::vector<std::string>    Bot::ft_split(std::string const & s, std::string const & seperator)
{
	std::vector<std::string> output;
	std::string::size_type prev_pos = 0, pos = 0;
	while((pos = s.find(seperator, pos)) != std::string::npos)
	{
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

void	Bot::cmdPars(std::string const & str)
{
	std::vector<std::string>	cmd;
	if(str[str.length() - 2] == '\r')
		cmd = ft_split(str, "\r\n");
	else
		cmd = ft_split(str, "\n");
	std::map<std::string, pfunc>::iterator	itMap;
	std::vector<std::string>::iterator	it = cmd.begin();
	for (; it != cmd.end(); it++)
	{
		if (VERBOSE)
			std::cout << BLUE + "<< " + *it + RESET << std::endl;
		std::vector<std::string>	cmds = splitCmd(*it, " ");
		if (!isRegistered && cmds[1] != "NOTICE" && cmds[0] != "PING")
		{
			if (cmds[1]	!= "001")
				throw std::runtime_error("Failed to register");
			std::string	botJoin("JOIN #bot\r\n");
			send(sock, botJoin.c_str(), botJoin.length(), 0);
			isRegistered = true;
		}
		if (cmds[0][0] == ':')
		{
			std::transform(cmds[1].begin(), cmds[1].end(), cmds[1].begin(), toupper);
			itMap = cmdMap.find(cmds[1]);
		}
		else
		{
			std::transform(cmds[0].begin(), cmds[0].end(), cmds[0].begin(), toupper);
			itMap = cmdMap.find(cmds[0]);
		}
		if (itMap != cmdMap.end())
			CALL_MEMBER_FN(*this, itMap->second) (cmds);
	}
}