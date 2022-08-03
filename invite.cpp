/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:32:34 by misaev            #+#    #+#             */
/*   Updated: 2022/08/03 19:33:50 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void    Command::invite(std::vector<std::string> cmds, Client & client)
{
	if (!client.getRegistered())
	{
		sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return ;
	}
	if (cmds.size() < 2)
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return ;
	}
	std::list<Client>::iterator	it = clients.begin();
	for (; it != clients.end(); it++)
		if (it->getNick() == cmds[1])
			break;
	if (it == clients.end())
	{
        sendMsg(client, "401", cmds[1], ERR_NOSUCHNICK);
        return;
	}
	if (!client.isInChan(cmds[2]))
	{
		sendMsg(client, "442", cmds[2], ERR_NOTONCHANNEL);
		return;
	}
	if (!chanMap[cmds[2]].isChanOp(client))
	{
		sendMsg(client, "482", cmds[2] + " ", ERR_CHANOPRIVSNEEDED);
		return;
	}
	if (it->isInChan(cmds[2]))
	{
		sendMsg(client, "443", cmds[1] + " " + cmds[2], ERR_USERONCHANNEL);
		return;
	}
	std::map<std::string, Channel>::iterator	itMap;
	
	sendMsg(client, "341", cmds[1] + " " + cmds[2], "");
	sendConfirmTo(*it, client, cmds[0] + " " + it->getNick(), cmds[2]);
	if (it->getAway().first)
	{
		sendMsg(client, "301", it->getNick(), it->getAway().second);
		return;
	}
}