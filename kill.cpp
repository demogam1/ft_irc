/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:07 by misaev            #+#    #+#             */
/*   Updated: 2022/07/22 19:37:20 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::kill(std::vector<std::string> cmds, Client &client)
{
	if (!client.getRegistered())
	{
		sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return;
	}
	if (!client.getOperator())
	{
		sendMsg(client, "481", "", ERR_NOPRIVILEGES);
		return;
	}
	if (cmds.size() < 2)
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return;
	}
	std::list<Client>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (cmds[1] == it->getNick())
		{
			std::vector<std::string>::iterator itChan = it->getChannels().begin();
			if (itChan != it->getChannels().end())
			{
				std::vector<std::string> partCmd(1, "PART");
				partCmd.push_back("");
				partCmd.push_back(":Killed by an operator");
				for (; itChan != it->getChannels().end(); itChan++)
					partCmd[1].append(*itChan + ",");
				part(partCmd, *it);
			}
			if (cmds.size() > 2)
			{
				if (cmds[2][0] == ':')
					cmds[2].erase(0, 1);
				sendConfirmTo(*it, client, cmds[0], cmds[2]);
			}
			else
				sendConfirmTo(*it, client, cmds[0], it->getNick());
			std::cout << "Host disconnected, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
			close(it->getSocket());
			it->setbeDeleted(true);
			return;
		}
	}
	sendMsg(client, "401", cmds[1], ERR_NOSUCHNICK);
}
