/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:59:11 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/24 17:41:36 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::quit(std::vector<std::string> cmds, Client &client)
{
	if (client.getRegistered())
	{
		if (cmds.size() > 1 && client.getConnected())
		{
			if (cmds[1][0] == ':')
				cmds[1].erase(0, 1);
			sendConfirm(client, cmds[0], cmds[1]);
		}
		else if (client.getConnected())
			sendConfirm(client, cmds[0], client.getNick());
		std::vector<std::string>::iterator it = client.getChannels().begin();
		std::map<std::string, Channel>::iterator	itMap;
		for (; it != client.getChannels().end(); it++)
		{
			itMap = chanMap.find(*it);
			itMap->second.deleteClient(&client);
			if(itMap->second.chanEmpty())
				chanMap.erase(itMap);
		}
		std::list<Client>::iterator itClient = clients.begin();
		for (; itClient != clients.end(); itClient++)
		{
			if (&(*itClient) != &client)
			{
				for (it = client.getChannels().begin(); it != client.getChannels().end(); it++)
				{
					if (itClient->isInChan(*it))
					{
						if (cmds.size() > 1)
						{
							if (cmds[1][0] == ':')
								cmds[1].erase(0, 1);
							sendConfirmTo(*itClient, client, cmds[0], cmds[1]);
						}
						else
							sendConfirmTo(*itClient, client, cmds[0], client.getNick());
						break;
					}
				}
			}
		}
	}
	if (client.getConnected())
		sendError(client, "Closing Link", client.getIP() + " (Client Quit)");
	if (VERBOSE)
		std::cout << UNDER + "Host disconnected, socket fd : " << client.getSocket() << ", IP : " << client.getIP() << ", port : " << client.getPort() << RESET << std::endl;
	close(client.getSocket());
	client.setbeDeleted(true);
}
