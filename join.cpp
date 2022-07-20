/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:13:55 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 18:08:16 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::join(std::vector<std::string> cmds, Client & client)
{
	client.okay.push_back("okay");
	chanMap[cmds[1]] = Channel();
	chanMap[cmds[1]].addClient(&client);
	std::cout << "join \n";
}
