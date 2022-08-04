/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:22:29 by misaev            #+#    #+#             */
/*   Updated: 2022/08/04 11:30:22 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void	Command::notice(std::vector<std::string> cmds, Client & client)
{
    if(!client.getRegistered())
    {
        sendMsg(client, "451","", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() == 3)
    {
        std::list<Client>::iterator	it = clients.begin();
        for (; it != clients.end(); it++)
            if (cmds[1] == it->getNick())
                break;
        if (it != clients.end())
        {
            sendConfirmTo(*it, client, cmds[0] + " " + cmds[1], cmds[2]);
            return;
        }
    }
    return;
}