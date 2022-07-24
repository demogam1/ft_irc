/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/07/24 17:20:46 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::mode(std::vector<std::string> cmds, Client & client)
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
    if (cmds[1][0] != '#')
    {
        if (cmds[1] != client.getNick())
        {
            sendMsg(client, "502", "", ERR_USERSDONTMATCH);
            return;
        }
        int sign = '+';
        int error_nbr = 0;
        for (size_t i = 0;i < cmds[2].length(); i++)
        {
            if (cmds[2][i] == '-')
                sign = '-';
            else if (cmds[2][i] == '+')
                sign = '+';
            else if (cmds[2][i] == 'o')
            {
                if (sign == '-')
                {    
                    if(client.getOperator() == true)
                    {
                        client.setOperator(false);
                        sendSpecConfirm(client , IP, cmds[0], cmds[1]);
                    }
                }
            }
            else if (error_nbr == 0 && cmds[2][i] != 'o')
            {
                sendMsg(client, "501", "", ERR_UMODEUNKNOWNFLAG);
                error_nbr++;
            }
        }
    }
    else if (cmds[1][0] == '#')
    {
        std::map<std::string, Channel>::iterator	itMap;
        if ((itMap = chanMap.find(cmds[1])) != chanMap.end())
        {
            std::cout << "le channel existe\n";
            if (client.isInChan(cmds[1]) == true)
            {
                std::cout << "le client est dans le channel\n";
                if(itMap->second.isChanOp(client) == true)
                {
                    std::cout << "le client est op dans le channel" << std::endl ;
                    return;
                }
                else
                {
                    std::cout << "le client n est pas op dans le channel" << std::endl;
                    return;
                }
                return;
            }
            else if (client.isInChan(cmds[1]) == false)
            {
                std::cout << "le client n est pas dans le channel\n";
                return;
            }
        }
        else
        {
            std::cout << "le channel n existe pas\n";
            return;
        }
    }
    return;
}