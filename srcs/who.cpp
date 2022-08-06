/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:41:53 by misaev            #+#    #+#             */
/*   Updated: 2022/08/06 16:18:19 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void	Command::who(std::vector<std::string> cmds, Client & client)
{
    if(!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() == 1)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    } 
    std::list<Client>::iterator	it = clients.begin();
	std::map<std::string, Channel>::iterator	itMap = chanMap.begin();
    std::string message;
    std::string channel;
    if (cmds[1][0] == '#')
    {
        for (; itMap != chanMap.end(); itMap++)
        {
            if (itMap->first == cmds[1])
            {
                for(; it != clients.end(); it++)
                {
                    if (!message.empty())
                        message = "";
                    if (itMap->second.isChanOp(*it) == true)
                        message.append("H@ :0 " + it->getRealname() + " ");
                    else if (it->isInChan(itMap->first) == true)
                        message.append("H :0 " + it->getRealname() + " ");
                    sendMsg(client, "352", cmds[1] + " ~" + it->getUser() + " " + it->getIP() + " " + IP + " " + it->getNick() , message);
                }
            }
        }
        sendMsg(client, "315", cmds[1], RPL_ENDOFWHO);
    }
    else
    {
        for(; it != clients.end(); it++)
        {
            if (it->getNick() == cmds[1])
            {
                for (; itMap != chanMap.end(); itMap++)
                {
                    if (it->isInChan(itMap->first))
                    {
                        if (itMap->second.isChanOp(*it) == true)
                        {
                            channel.append(itMap->first);
                            message.append("H@ :0 " + it->getRealname() + " ");
                            break;
                        }
                        else
                        {
                            channel.append(itMap->first);
                            message.append("H :0 " + it->getRealname() + " ");
                            break;
                        }
                    }
                }
                if (itMap == chanMap.end())
                {
                    channel.append("* ");
                    message.append("H :0" + it->getRealname() + " ");
                }
                sendMsg(client, "352", channel + " ~" + it->getUser() + " " + it->getIP() + " " + IP + " " + it->getNick() , message);
            }
        }
        sendMsg(client, "315", cmds[1], RPL_ENDOFWHO);
    }
    return;
}
