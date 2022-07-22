/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:29:35 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 12:17:24 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

void	Channel::addClient(Client * client)
{
	clients.push_back(client);
}

void	Channel::addChanOp(Client * client)
{
	clients.push_back(client);
}

void	Channel::deleteClient(Client * client)
{
	std::vector<Client *>::iterator	it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (client == *it)
		{
			clients.erase(it);
			return ;
		}
	}
	for (it = chanOp.begin(); it != chanOp.end(); it++)
	{
		if (client == *it)
		{
			clients.erase(it);
			return ;
		}
	}
}
void    Channel::sendConfirmChan(Client const & client, std::string const & cmd, std::string const & opt)
{
	std::string message(":" + CLIENT);
	message += " " + cmd + " :" + opt + "\r\n";
	std::vector<Client *>::iterator	it = clients.begin();
	for(; it != clients.end(); it++)
		if (*it != &client)
			send((*it)->getSocket(), message.c_str(), message.length(), 0);
	for(it = chanOp.begin(); it != chanOp.end(); it++)
		if (*it != &client)
			send((*it)->getSocket(), message.c_str(), message.length(), 0);
}