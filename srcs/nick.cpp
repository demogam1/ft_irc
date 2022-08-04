/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:56:14 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/04 11:30:18 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void	Command::nick(std::vector<std::string> cmds, Client & client)
{
	if (cmds.size() == 1)
	{
		sendMsg(client, "431", "", ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (cmds[1].length() > 8)
		cmds[1].resize(9);
	std::list<Client>::iterator	it = clients.begin();
	for(; it != clients.end(); it++)
		if (cmds[1] == it->getNick() && &(*it) != &client)
		{
			sendMsg(client, "433", cmds[1], ERR_NICKNAMEINUSE);
			return ;
		}
	if ((!isalpha(cmds[1][0]) && !isSpecial(cmds[1][0])))
	{
		sendMsg(client, "432", cmds[1], ERR_ERRONEUSNICKNAME);
		return;
	}
	for (size_t i = 1; i < cmds[1].length(); i++)
	{
		if (!isalpha(cmds[1][i]) && !isSpecial(cmds[1][i]) && !isdigit(cmds[1][i]))
		{
			sendMsg(client, "432", cmds[1], ERR_ERRONEUSNICKNAME);
			return;
		}
	}
	if (client.getNick() != cmds[1])
	{
		if (client.getRegistered())
			sendConfirm(client, cmds[0], cmds[1]);
		client.setNick(cmds[1]);
	}
	if (!client.getRegistered())
	{
		client.setNicked(true);
		registerClient(client);
	}
}
