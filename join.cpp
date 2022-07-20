/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:13:55 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 19:49:40 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::join(std::vector<std::string> cmds, Client & client)
{
	if (!client.getRegistered())
	{
		sendMsg(client, "451", "", ERR_NOTREGISTERED);
		return ;
	}
	if (cmds.size() <= 1)
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return ;
	}
	if (chanMap.find(cmds[1]) == chanMap.end())
	{
		chanMap[cmds[1]] = Channel();
		chanMap[cmds[1]].addClient(&client);
		client.getChannels().push_back(cmds[1]);
	}
}
