/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/07/26 16:12:26 by misaev           ###   ########.fr       */
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
                        else if (cmds[2][i] == 'o')
                        {
                            if (sign == '-')
                            {    
                               
                               return;
                            }
                            if (sign == '+')
                            {
                                std::cout << "you are now the operator in this channel\n";
                                return;
                            }
                        }
                        else if (cmds[2][i] == 'i')
                        {
                            if (sign == '-')
                            {
                                std::cout << "the invitation mode is set off\n";
                                return;
                            }
                            if (sign == '+')
                            {
                                std::cout << "the inviation mode is set on";
                                return; 
                            }
                        }
                        else if (cmds[2][i] == 't')
                        {
                            if (sign == '-')
                            {
                               std::cout << "the topic in this channel has been removed\n";
                               return; 
                            }
                            if (sign == '+')
                            {
                                std::cout << "the topic in this channel has been set\n";
                                return;
                            }
                        }
                        else if (cmds[2][i] == 'k')
                        {
                            if (sign == '-')
                            {
                               std::cout << "the password has been removed\n";
                               return; 
                            }
                            if (sign == '+')
                            {
                                std::cout << "the password has been set\n";
                                return;
                            }
                        }
                        else if (error_nbr == 0 && cmds[2][i] != 'o' && cmds[2][i] != 'w' && cmds[2][i] != 'O' && cmds[2][i] != 'i' && cmds[2][i] != 's' && cmds[2][i] != 'r' && cmds[2][i] != 'a')
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