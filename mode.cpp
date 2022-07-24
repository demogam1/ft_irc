/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/07/24 18:01:10 by asebrech         ###   ########.fr       */
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
    if (cmds[1] != client.getNick())
    {
        sendMsg(client, "502", "", ERR_USERSDONTMATCH);
        return;
    }
   
    else
    {
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
    return;
}