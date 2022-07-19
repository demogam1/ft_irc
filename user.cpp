/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:58:19 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/19 17:58:54 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::user(std::vector<std::string> cmds, Client & client)
{
	if (client.getRegistered())
	{
		sendMsg(client, "462", "", ERR_ALREADYREGISTRED);
		return;
	}
	if (cmds.size() <= 4 || cmds[4] == ":")
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return;
	}
	client.setUser(cmds[1]);
	client.setMode(cmds[2]);
	client.setUnused(cmds[3]);
	if (cmds[4][0] == ':')
		cmds[4].erase(0, 1);
	client.setRealname(cmds[4]);
	client.setUsered(true);
	registerClient(client);
}
