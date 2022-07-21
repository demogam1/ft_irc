/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:55:54 by misaev            #+#    #+#             */
/*   Updated: 2022/07/21 14:16:37 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::pong(std::vector<std::string> cmds, Client & client)
{
    if (cmds.size() == 1)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
    else if (cmds.size() == 2)
    {
        sendSpecConfirm(client, IP, "PONG", cmds[1]);
        return;
    }
    else
    {
        if (cmds[2] != IP)
        {
            sendMsg(client, "408", cmds[2], ERR_NOSUCHSERVICE);
            return;
        }
        else
        {
            sendSpecConfirm(client, IP, "PONG", cmds[1]);
            return;
        }
    }
}