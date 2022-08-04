/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:28:48 by misaev            #+#    #+#             */
/*   Updated: 2022/08/04 11:29:30 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void	Command::away(std::vector<std::string> cmds, Client & client)
{
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() == 1)
    {
        client.setAway(std::pair<bool, std::string>(false, ""));
        sendMsg(client, "305", "", RPL_UNAWAY);
        return;
    }
    if (cmds.size() > 1)
    {
        client.setAway(std::pair<bool, std::string>(true, cmds[1]));
        sendMsg(client, "306", "", RPL_NOWAWAY);
        return;
    }
}