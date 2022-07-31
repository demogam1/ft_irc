/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/07/31 15:33:06 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::mode(std::vector<std::string> cmds, Client & client)
{
    int error_nbr = 0;
    int sign = '+';
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
                        sendSpecConfirm(client , client.getNick(), cmds[0], cmds[2]);
                    }
                }
            }
            else if (error_nbr == 0 && cmds[2][i] != 'o' && cmds[2][i] != 'w' && cmds[2][i] != 'O' && cmds[2][i] != 'i' && cmds[2][i] != 's' && cmds[2][i] != 'r' && cmds[2][i] != 'a')
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
            if (client.isInChan(cmds[1]) == true)
            {
                if(itMap->second.isChanOp(client) == true)
                {
                    for (size_t i = 0;i < cmds[2].length(); i++)
                    {    
                        if (cmds[2][i] == '-')
                            sign = '-';
                        else if (cmds[2][i] == '+')
                            sign = '+';
                        else if (cmds[2][i] == 'o' && cmds[2][i + 1] == 0)
                        {
                            if (cmds.size() < 4)
                            {
                                sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
                                return;
                            }
                            std::list<Client>::iterator	it = clients.begin();
                            for (; it != clients.end(); it++)
                                if (cmds[3] == it->getNick())
                                    break;
                            if (it == clients.end())
                            {
                                sendMsg(client, "401", "", ERR_NOSUCHNICK);
                                return;
                            }
                            if (it->isInChan(cmds[1]) == true)
                            {                                
                                if (sign == '-')
                                {
                                    if (itMap->second.isChanOp(*it) == true)
                                    {
                                        itMap->second.deleteChanOp(&(*it));
                                        sendSpecConfirm(client , client.getNick(), cmds[0], cmds[2]);
                                    }
                                    return;
                                }
                                if (sign == '+')
                                {
                                    if (itMap->second.isChanOp(*it) == false)
                                    {
                                        itMap->second.addChanOp(&(*it));                                
                                        sendSpecConfirm(client , client.getNick(), cmds[0], cmds[2]);
                                    }
                                    return;
                                }
                            }
                            else
                            {
                                sendMsg(client, "442", client.getNick() + " " +  cmds[3] + " " + cmds[1], ERR_USERNOTINCHANNEL);
                                return;
                            }
                        }
                        else if (cmds[2][i] == 'i' && cmds[2][i + 1] == 0)
                        {
                            if (sign == '-')
                            {
                                if (itMap->second.getInvite() == true)
                                {
                                    itMap->second.setInvite(false);
                                    sendConfirm(client , cmds[0] + " " + cmds[1] + " " + cmds[2], "");
                                }
                                return;
                            }
                            if (sign == '+')
                            {                                
                                if (itMap->second.getInvite() == false)
                                {
                                    itMap->second.setInvite(true);
                                    sendConfirm(client , cmds[0]  + " " + cmds[1] + " " + cmds[2], "");
                                }
                                return;
                            }
                        }
                        else if (cmds[2][i] == 't' && cmds[2][i + 1] == 0)
                        {
                            if (sign == '-')
                            {
                                if (itMap->second.getEnableTopic() == true)
                                {
                                    itMap->second.enableTopic(false);
                                    sendConfirm(client , cmds[0] + " " + cmds[1] + " " + cmds[2], "");
                                }
                                return;
                            }
                            if (sign == '+')
                            {
                                if (itMap->second.getEnableTopic() == false)
                                {
                                    itMap->second.enableTopic(true);
                                    sendConfirm(client , cmds[0] + " " + cmds[1] + " " + cmds[2], "");
                                }
                                return;
                            }
                        }
                        else if (cmds[2][i] == 'k' && cmds[2][i + 1] == 0)
                        {
                            if (sign == '-')
                            {
                                if (cmds.size() == 4 && cmds[3] == itMap->second.getPassword())
                                {
                                    itMap->second.setPassword("");
                                    sendConfirm(client , cmds[0] + " " + cmds[1] + " " + cmds[2] + " *", "");
                                }
                                return; 
                            }
                            if (sign == '+')
                            {
                                if (cmds.size() == 4)
                                {
                                    itMap->second.setPassword(cmds[3]);
                                    sendConfirm(client , cmds[0]  + " " + cmds[1] + " " + cmds[2] + " " + cmds[3], "");
                                }
                                return;
                            }
                        }
                        else if (error_nbr == 0 && cmds[2][i] != 'o' && cmds[2][i] != 'w' && cmds[2][i] != 'O' && cmds[2][i] != 'i' && cmds[2][i] != 's' && cmds[2][i] != 'r' && cmds[2][i] != 'a' && cmds[2][i] != 't')
                        {
                            sendMsg(client, "501", "", ERR_UMODEUNKNOWNFLAG);
                            error_nbr++;
                        }
                    }
                }
                else
                {
                    sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
                    return;
                }
            }
            else if (client.isInChan(cmds[1]) == false)
            {
                sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
                return;
            }
        }
        else
        {
            sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
            return;
        }
    }
    return;
}