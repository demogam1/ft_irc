/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 14:01:30 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/31 16:09:06 by misaev           ###   ########.fr       */
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
	std::string	botRegister;

	if (!pass.empty())
		botRegister += "PASS " + pass + "\r\n";
	
	botRegister += "NICK bot\r\nUSER autoBot bot * :Auto Bot\r\n";

	send(sock, botRegister.c_str(), botRegister.length(), 0);
	
	while((valread = recv(sock, buffer, 1024, 0)))
	{
		buffer[valread] = '\0';
		if (VERBOSE)
			std::cout << BLUE + "<< " + buffer + RESET;
		bzero(buffer, valread);
	}
	std::cout << YELLOW + "Connection lost" + RESET << std::endl;
}