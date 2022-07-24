/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:47:49 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/24 17:43:41 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string const & pass) : port(port), pass(pass), command(pass, clients, IP)
{
	myhostname();
	command.setIP(IP);
}

Server::Server() : port(4242), pass(""), command(pass, clients, IP)
{
	myhostname();
	command.setIP(IP);
}

Server::~Server()
{
	myhostname();
	command.setIP(IP);
}

void	Server::myhostname()
{
	char	host[256];
	struct hostent	*host_entry;
	gethostname(host, sizeof(host));
	host_entry = gethostbyname(host);
	IP = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
}

void	Server::init()
{
	int	opt = 1;

	if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
		throw std::runtime_error("socket");

	if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)  
		throw std::runtime_error("setsockopt");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
		throw std::runtime_error("bind failed");
	if (VERBOSE)
		std::cout << MAGENTA + UNDER + "Listener on port " << port << " pass is " << pass << RESET << std::endl;

	if (listen(master_socket, 3) < 0)  
		throw std::runtime_error("listen");
	addrlen = sizeof(address);
	if (VERBOSE)
		std::cout << MAGENTA + UNDER + "Waiting for connections ..." + RESET << std::endl << std::endl;
}

void	Server::run()
{
	int	sd;
	int	max_sd;
	int	ret;
	std::list<Client>::iterator	it;
	char	buffer[1024];

	while(true)
	{
		FD_ZERO(&readfds);
		FD_SET(master_socket, &readfds);  
		max_sd = master_socket;
		for (it = clients.begin(); it != clients.end(); it++)
		{
			if (it->getbeDeleted())
				it = clients.erase(it);
			sd = it->getSocket();		
			FD_SET(sd, &readfds);
			if (sd > max_sd)
				max_sd = sd;
		}
		ret = select(max_sd + 1 , &readfds , NULL , NULL , NULL);  
		if ((ret < 0) && (errno!=EINTR))  
			throw std::runtime_error("select error");
		if (FD_ISSET(master_socket, &readfds))  
		{
			if ((ret = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
				throw std::runtime_error("accept");
			Client	client(ret, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
			if (VERBOSE)
				std::cout << UNDER + "New connection, socket fd : " << client.getSocket() << ", IP : " << client.getIP() << ", port : " << client.getPort() << RESET << std::endl;
			clients.push_back(client);
		}
		for (it = clients.begin(); it != clients.end(); it++)
		{
			sd = it->getSocket();
			if (FD_ISSET(sd, &readfds))
			{
				if ((ret = recv(sd, (void*)buffer, 1024, 0)) == 0)
				{
					it->setConnected(false);
					it->getBuff().assign("QUIT :Remote host closed the connection\r\n");
				}
				else
				{
					buffer[ret] = '\0';
					it->getBuff().append(buffer);
				}
				if (it->getBuff()[it->getBuff().length() - 1] == '\n')
				{
					if (VERBOSE)
					{
						std::cout << "Command received, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
						std::cout << BLUE + "<< " + it->getBuff() + RESET;
					}
					command.parsCmd(*it);
					it->getBuff().clear();
				}
				bzero(buffer, ret);
			}
		}
	}
}
