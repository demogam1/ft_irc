/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:05:27 by misaev            #+#    #+#             */
/*   Updated: 2022/07/29 17:06:15 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::names(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return ;
	}
    std::map<std::string, Channel>::iterator itMap;
    std::list<Client>::iterator	it;
    if (cmds.size() == 1)
    {
        itMap = chanMap.begin();
        for (; itMap != chanMap.end(); itMap++)
        {
            it = clients.begin();
            sendConfirm(client, "353" , client.getNick() + " = " + itMap->first);
            for(; it != clients.end(); it++)
                std::cout << it->getNick() + " " << std::endl;
        }
    }
    return;
}