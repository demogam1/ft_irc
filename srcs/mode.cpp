/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/08/06 20:11:10 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"


void Command::mode(std::vector<std::string> cmds, Client & client)
{
    int error_nbr = 0;
    int sign = '+';
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() == 1)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
    if (cmds.size() == 2)
    {
        std::time_t result = std::time(nullptr);
        std::map<std::string, Channel>::iterator    itMap = chanMap.begin();    
        std::list<Client>::iterator	it = clients.begin();
        if (cmds[1][0] == '#')
        {
            if ((itMap = chanMap.find(cmds[1])) == chanMap.end())
                sendMsg(client, "403", cmds[1], ERR_NOSUCHCHANNEL);
            else
            {
                sendMsg(client, "324", cmds[1], usedMods(cmds[1]));
                sendMsg(client, "333", cmds[1], std::to_string((int)result));
            }
        }
        else
        {
            for(; it != clients.end(); it++)
            {
                if (it->getNick() == cmds[1])
                {
                    if (it->getAway().first == true)
                        sendMsg(client, "324", "", "+o");
                    else
                        sendMsg(client, "324", "", "+");
                    break;
                }
            }
            if (it == clients.end())
                sendMsg(client, "403", cmds[1], ERR_NOSUCHCHANNEL);
        }
    }
    else if (cmds[1][0] != '#')
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
    return;
}