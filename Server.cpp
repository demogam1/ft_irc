/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:47:49 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 18:05:03 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : port(4242), pass("1234"), command(pass, clients, IP)
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
	std::cout << "Listener on port " << port << " pass is " << pass << std::endl;

	if (listen(master_socket, 3) < 0)  
		throw std::runtime_error("listen");
	addrlen = sizeof(address);
	std::cout << "Waiting for connections ..." << std::endl;
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
			std::cout << "New connection, socket fd : " << client.getSocket() << ", IP : " << client.getIP() << ", port : " << client.getPort() << std::endl;
			clients.push_back(client);
		}
		for (it = clients.begin(); it != clients.end(); it++)
		{
			sd = it->getSocket();
			if (FD_ISSET(sd, &readfds))
			{
				if ((ret = recv(sd, (void*)buffer, 1024, 0)) == 0)
				{
					std::cout << "Host disconnected, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
					close(sd);
					it = clients.erase(it);
				}	
				else
				{
					buffer[ret] = '\0';
					it->getBuff().append(buffer);
					if (it->getBuff()[it->getBuff().length() - 1] == '\n')
					{
						std::cout << "Command received, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
						std::cout << buffer;
						command.parsCmd(*it);
						it->getBuff().clear();
						if (it->getbeDeleted())
						{
							std::cout << "Host disconnected, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
							close(sd);
							it = clients.erase(it);
						}
					}
					bzero(buffer, ret);
				}
			}
		}
	}
}
