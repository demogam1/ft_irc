/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:50:37 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 15:28:45 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::part(std::vector<std::string> cmds, Client &client)
{
	if (!client.getRegistered())
	{
		sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return;
	}
	if (cmds.size() < 2)
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return;
	}
	std::vector<std::string> chans = splitChan(cmds[1], ",");
	std::vector<std::string>::iterator it = chans.begin();
	std::map<std::string, Channel>::iterator itMap;
	for (; it != chans.end(); it++)
	{
		if ((itMap = chanMap.find(*it)) == chanMap.end())
			sendMsg(client, "403", cmds[0], *it + ERR_NOSUCHCHANNEL);
		else
		{
			if (client.isInChan(*it))
			{
				itMap->second.deleteClient(&client);
				client.deleteChan(*it);
				if (cmds.size() > 2)
				{
					if (cmds[2][0] == ':')
						cmds[2].erase(0, 1);
					sendConfirm(client, cmds[0] + " " + cmds[1], cmds[2]);
					itMap->second.sendConfirmChan(client, cmds[0] + " " + cmds[1], cmds[2]);
				}
				else
				{
					sendConfirm(client, cmds[0] + " " + cmds[1], "");
					itMap->second.sendConfirmChan(client, cmds[0] + " " + cmds[1], "");
				}
			}
			else
				sendMsg(client, "403", cmds[0], *it + ERR_NOTONCHANNEL);
		}
	}
}