/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:39:53 by misaev            #+#    #+#             */
/*   Updated: 2022/08/06 16:42:27 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void Command::whois(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() == 1)
    {
        sendMsg(client, "431", "", ERR_NONICKNAMEGIVEN);
        return;
    }
    std::list<Client>::iterator	it = clients.begin();
	std::map<std::string, Channel>::iterator	itMap = chanMap.begin();
    std::time_t result = std::time(nullptr);
	for(; it != clients.end(); it++)
		if (cmds[1] == it->getNick())
			break;
    if (it == clients.end())
    {
        sendMsg(client, "401", cmds[1], ERR_NOSUCHNICK);
        return;
    }
    sendMsg(client, "311", it->getNick() + " ~" + it->getUser() + " " + it->getIP() + " *" , ":" + it->getRealname());
    sendMsg(client, "312", it->getNick() + " " + IP , ":Nice, FR");
    if (it->getAway().first)
    {
        if (it->getAway().second[0] == ':')
            sendMsg(client, "301", it->getNick(), it->getAway().second);
        else
            sendMsg(client, "301", it->getNick(), ":" + it->getAway().second);
    }
    std::string operChan;
    for(; itMap != chanMap.end(); itMap++)
    {
        if (itMap->second.isChanOp(*it))
            operChan.append("@" + itMap->first + " ");         
    }
    if (operChan.size() > 0)
        sendMsg(client, "319",it->getNick(), ":" + operChan);
    sendMsg(client, "338", it->getNick() + " " + it->getIP(), ":actually using host");
    sendMsg(client, "317", it->getNick() + " " + std::to_string((int)result), ":seconds idle, signon time");
    sendMsg(client, "318", it->getNick(), RPL_ENDOFWHOIS);
    return;
}