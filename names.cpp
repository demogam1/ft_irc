/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:05:27 by misaev            #+#    #+#             */
/*   Updated: 2022/08/04 10:59:34 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::names(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return ;
	}
    std::map<std::string, Channel>::iterator itMap;
    std::list<Client>::iterator	itClient;
    if (cmds.size() == 1)
    {
        itMap = chanMap.begin();
        std::string message;
        std::string channel;
        for (; itMap != chanMap.end(); itMap++)
        {
            itClient = clients.begin();
            if (!message.empty())
                message = "";
            if (!channel.empty())
                channel = "";
            for(; itClient != clients.end(); itClient++)
            {
                if (itMap->second.isChanOp(*itClient) == true)
                    message.append("@" + itClient->getNick() + " ");
                else if (itClient->isInChan(itMap->first) == true)
                    message.append(itClient->getNick() + " ");
                else if (itClient->getChannels().size() == 0)
                    channel.append(itClient->getNick() + " ");
            }
            if (channel.size() > 0)
                sendMsg(client, "353", "* * :", channel);
            sendMsg(client, "353", "= " + itMap->first + " :", message);
        }
    }
    else if (cmds.size() > 1)
    {
        std::vector<std::string>	keys;
        std::vector<std::string>::iterator	iChan;
        std::string message;
        keys = ft_split(cmds[1], ",");
        iChan = keys.begin();
        for (; iChan != keys.end(); iChan++)
        {
            if (!message.empty())
                message = "";
            itMap = chanMap.begin();
            for (; itMap != chanMap.end(); itMap++)
            {
                if (itMap->first == *iChan)
                {
                    itClient = clients.begin();
                    for (; itClient != clients.end(); itClient++)
                    {
                        if (itMap->second.isChanOp(*itClient) == true)
                            message.append("@" + itClient->getNick() + " ");
                        else if (itClient->isInChan(itMap->first) == true)
                            message.append(itClient->getNick() + " ");
                    }
                    sendMsg(client, "353", "= " + itMap->first + " :", message);
                }
            }
        }
    }
    if (cmds.size() == 1)
        sendMsg(client, "366", "", "* :End of /NAMES list.");
    else    
        sendMsg(client, "366", cmds[1] +  " :End of", "/NAMES list.");
    return;
}