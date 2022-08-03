/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:05:27 by misaev            #+#    #+#             */
/*   Updated: 2022/08/02 15:26:06 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::list(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return ;
	}
    std::map<std::string, Channel>::iterator itMap;
    std::list<Client>::iterator	itClient;
    sendMsg(client, "321", "", "Channel :Users  Name");
    if (cmds.size() == 1)
    {
        itMap = chanMap.begin();
        std::string message;
        for (; itMap != chanMap.end(); itMap++)
        {
            std::string channel(itMap->first);
            itClient = clients.begin();
            if (!message.empty())
                message = "";
            for(; itClient != clients.end(); itClient++)
            {
                if (itClient->isInChan(channel) == true)
                    message.append(itMap->second.getTopic());
            }
            if (message[0] == ':')
                message.erase(0,1);
            sendMsg(client, "322", channel + " :", message);
        }
    }
    else if (cmds.size() > 1)
    {
        std::vector<std::string>	keys;
        std::vector<std::string>::iterator	iChan;
        std::string message;
        keys = splitChan(cmds[1], ",");
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
                        if (itClient->isInChan(itMap->first) == true)
                            message.append(itMap->second.getTopic());
                    }
                    if (message[0] == ':')
                        message.erase(0,1);
                    sendMsg(client, "322", itMap->first + " :", message);
                }
            }
        }
    }
    if (cmds.size() == 1)
        sendMsg(client, "323", "", ":End of /NAMES list.");
    else    
        sendMsg(client, "323", cmds[1] +  " :End of", "/NAMES list.");
    return;
}