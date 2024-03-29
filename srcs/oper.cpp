/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:15:02 by misaev            #+#    #+#             */
/*   Updated: 2022/08/04 11:30:25 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void Command::oper(std::vector<std::string> cmds, Client & client)
{
	if (!client.getRegistered())
	{
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
	}
	size_t	a = 3;
	if (password.empty())
		a = 2;
    if (cmds.size() < a)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
	std::list<Client>::iterator	it = clients.begin();
	for (; it != clients.end(); it++)
		if (cmds[1] == it->getNick())
			break;
    if (it == clients.end() || !it->getRegistered())
    {
        sendMsg(client, "491", "", ERR_NOOPERHOST);
        return;
    }
    if (!password.empty() && cmds[2] != password)
    {
        sendMsg(client, "464", "", ERR_PASSWDMISMATCH);
        return;
    }
	if (!it->getOperator())
	{
    	it->setOperator(true);
    	sendMsg(*it, "381", "", RPL_YOUREOPER);
	}
    return;
}
