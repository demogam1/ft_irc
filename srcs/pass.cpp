/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:57:14 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/04 11:30:32 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void	Command::pass(std::vector<std::string> cmds, Client & client)
{
	if (cmds.size() == 1)
	{
		sendMsg(client, "461", "", ERR_NEEDMOREPARAMS);
		return ;
	}
	if (client.getRegistered())
	{
		sendMsg(client, "462", "", ERR_ALREADYREGISTRED);
		return;
	}
	client.setPass(cmds[1]);
}
