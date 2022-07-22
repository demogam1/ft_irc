/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:07 by misaev            #+#    #+#             */
/*   Updated: 2022/07/22 11:00:01 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::kill(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;   
    }
    if (!client.getOperator())
    {
        sendMsg(client, "481", "", ERR_NOPRIVILEGES);
        return;
    }
    if (cmds.size() < 3)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
    std::list<Client>::iterator it;
    for (it = clients.begin(); it != clients.end(); it++)
    {
        if (cmds[1] == it->getNick())
        {
            sendConfirmTo(*it, client, cmds[0], "Client Kill");
            if (cmds[2][0] == ':')
		        cmds[2].erase(0, 1);
            sendError(*it, "KILL REASON", "[" + cmds[2] + "]");
            std::cout << "Host disconnected, socket fd : " << it->getSocket() << ", IP : " << it->getIP() << ", port : " << it->getPort() << std::endl;
            close(it->getSocket());
            it->setbeDeleted(true);
            return;            
        }
    }
    sendMsg(client, "401", cmds[1], ERR_NOSUCHNICK);
}

