/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:55:54 by misaev            #+#    #+#             */
/*   Updated: 2022/08/03 18:27:21 by misaev           ###   ########.fr       */
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
    sendSpecConfirm(client, IP, "PONG", cmds[1]);
    return;
}