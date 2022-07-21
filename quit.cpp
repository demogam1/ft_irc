/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:59:11 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/21 15:39:13 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::quit(std::vector<std::string> cmds, Client & client)
{
	if (client.getRegistered())
		sendConfirm(client, cmds[0], "Client Quit");
	sendError(client,"Closing Link", client.getIP() + " (Client Quit)");
	std::cout << "Host disconnected, socket fd : " << client.getSocket() << ", IP : " << client.getIP() << ", port : " << client.getPort() << std::endl;
	close(client.getSocket());
	client.setbeDeleted(true);
}
