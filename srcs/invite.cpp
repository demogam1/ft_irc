/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:32:34 by misaev            #+#    #+#             */
/*   Updated: 2022/08/04 14:29:56 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

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
	sendMsg(client, "341", cmds[1] + " " + cmds[2], "");
	sendConfirmTo(*it, client, cmds[0] + " " + it->getNick(), cmds[2]);
	std::map<std::string, Channel>::iterator	itMap;
	if ((itMap = chanMap.find(cmds[2])) != chanMap.end())
	{
		itMap->second.addInvited(&(*it));
		std::cout << itMap->first << std::endl;	
	}
	else
	{
		sendMsg(client, "401", cmds[1], ERR_NOSUCHNICK);
		return;
	}
	if (it->getAway().first)
	{
		sendMsg(client, "301", it->getNick(), it->getAway().second);
		return;
	}
}