/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:15:02 by misaev            #+#    #+#             */
/*   Updated: 2022/07/19 20:37:14 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::oper(std::vector<std::string> cmds, Client & client)
{
    if (cmds.size() < 3)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
    else if (strcmp(cmds[1].c_str(), client.getRealname().c_str()))
    {
        sendMsg(client, "491", "", ERR_NOOPERHOST);
        return;
    }
    else if (strcmp(cmds[2].c_str(), password.c_str()))
    {
        sendMsg(client, "464", "", ERR_PASSWDMISMATCH);
        return;
    }
    client.setOperator(true);
    sendMsg(client, "381", "", RPL_YOUREOPER);
    std::cout << client.getOperator() << std::endl;
    return;
}