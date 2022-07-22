/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:59:11 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 11:01:33 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::quit(std::vector<std::string> cmds, Client &client)
{
	if (client.getRegistered())
	{
		sendConfirm(client, cmds[0], "Client Quit");
		std::vector<std::string>::iterator it;
		std::list<Client>::iterator itClient = clients.begin();
		for (; itClient != clients.end(); itClient++)
		{
			if (&(*itClient) != &client)
			{
				for (it = client.getChannels().begin(); it != client.getChannels().end(); it++)
				{
					if (itClient->isInChan(*it))
					{
						sendConfirmTo(*itClient, client, cmds[0], "Client Quit");
						break;
					}
				}
			}
		}
	}
	sendError(client, "Closing Link", client.getIP() + " (Client Quit)");
	std::cout << "Host disconnected, socket fd : " << client.getSocket() << ", IP : " << client.getIP() << ", port : " << client.getPort() << std::endl;
	close(client.getSocket());
	client.setbeDeleted(true);
}
