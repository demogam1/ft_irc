/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:01:30 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/31 22:35:29 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot() : port(4242), pass(""), IP("127.0.0.1"), sock(0) {}

Bot::Bot(int port, std::string const & pass, std::string const & IP) : port(port), pass(pass), IP(IP), sock(0) {}

Bot::~Bot() { close(client_fd); }

void	Bot::init()
{
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Socket creation error");
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	
	if (inet_pton(AF_INET, IP.c_str(), &serv_addr.sin_addr) <= 0)
		throw std::runtime_error("Invalid address / Address not supported");
	
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
	
	botRegister += "NICK bot\r\nUSER autoBot bot * :Auto Bot\r\n";

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

void	Bot::cmdPars(std::string const & str)
{
	int	registerBot = 0;
	std::vector<std::string>	cmd;
	if(str[str.length() - 2] == '\r')
		cmd = splitCmd(str, "\r\n");
	else
		cmd = splitCmd(str, "\n");
	std::vector<std::string>::iterator	it = cmd.begin();
	for (; it != cmd.end(); it++)
	{
		if (registerBot == 0)
		{

		}
		std::vector<std::string>	cmds = splitCmd(*it, " ");
		std::transform(cmds[0].begin(), cmds[0].end(),cmds[0].begin(), toupper);
		std::vector<std::string>::iterator	itt = cmds.begin();

		for (; itt != cmds.end(); itt++)
		std::cout << *itt << std::endl;
		//std::cout << *it;
	}
}