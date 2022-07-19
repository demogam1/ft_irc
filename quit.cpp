/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:59:11 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/19 17:59:44 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::quit(std::vector<std::string> cmds, Client & client)
{
	if (client.getRegistered())
		sendConfirm(client, cmds[0], "Client Quit");
	sendError(client,"Closing Link", client.getIP() + " (Client Quit)");
	client.setbeDeleted(true);
}
