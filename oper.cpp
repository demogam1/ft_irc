/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:15:02 by misaev            #+#    #+#             */
/*   Updated: 2022/07/20 10:04:10 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::oper(std::vector<std::string> cmds, Client & client)
{
	if (!client.getRegistered())
	{
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
	}
    if (cmds.size() < 3)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
	Client	clientOP(client);
	std::list<Client>::iterator	it = clients.begin();
	if (client.getUser() != cmds[1])
	{
		for (; it != clients.end(); it++)
			if (cmds[1] == it->getUser())
			{
				clientOP = *it;
				break;
			}
	}
    if (it == clients.end() || !clientOP.getRegistered())
    {
        sendMsg(client, "491", "", ERR_NOOPERHOST);
        return;
    }
    if (cmds[2] != password)
    {
        sendMsg(client, "464", "", ERR_PASSWDMISMATCH);
        return;
    }
	if (!clientOP.getOperator())
	{
    	client.setOperator(true);
    	sendMsg(clientOP, "381", "", RPL_YOUREOPER);
	}
    return;
}
