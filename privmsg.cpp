/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:17:25 by misaev            #+#    #+#             */
/*   Updated: 2022/07/28 18:32:15 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::privatmsg(std::vector<std::string> cmds, Client & client)
{
    if(!client.getRegistered())
    {
        sendMsg(client, "451","", ERR_NOTREGISTERED);
        return;
    }
    if(cmds.size() == 1)
    {
        sendMsg(client, "411", "", ERR_NORECIPIENT);
        return ;
    }
    if(cmds.size() == 2)
    {
        sendMsg(client, "412", "", ERR_NOTEXTTOSEND);
        return;
    }
    if (cmds[1][0] == '#')
    {
        std::map<std::string, Channel>::iterator	itMap;
        if ((itMap = chanMap.find(cmds[1])) != chanMap.end())
        {
            itMap->second.sendConfirmChan(client, cmds[0] + " " + cmds[1], cmds[2]);
            return;
        }
        else
        {
            sendMsg(client, "404", cmds[1], ERR_NOSUCHNICK);
            return;
        }
    }
    else
    {
        std::list<Client>::iterator	it = clients.begin();
        for (; it != clients.end(); it++)
            if (cmds[1] == it->getNick())
                break;
        if (it == clients.end())
        {
            sendMsg(client, "401", "", ERR_NOSUCHNICK);
            return;
        }
        else
        {
            if (it->getAway().first == true)
                sendMsg(client, "301", it->getNick() ,it->getAway().second);
            if (cmds[2][0] == ':')
                cmds[2].erase(0, 1);
            sendConfirmTo(*it, client, cmds[0] + " " + cmds[1], cmds[2]);
            return;
        }
    }
}