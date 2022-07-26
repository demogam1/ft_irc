/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:13:55 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/26 15:33:07 by asebrech         ###   ########.fr       */
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
	if (cmds.size() < 2)
	{
		sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
		return ;
	}
	std::vector<std::string>	chans = splitChan(cmds[1], ",");
	std::vector<std::string>	keys;
	if (cmds.size() > 2)
		keys = splitChan(cmds[2], ",");
	std::vector<std::string>::iterator	it = chans.begin();
	std::vector<std::string>::iterator	itKey = keys.begin();
	std::map<std::string, Channel>::iterator	itMap;
	for(; it != chans.end(); it++)
	{
		if (it->length() > 50 || (*it)[0] != '#')
			sendMsg(client, "403", cmds[0], *it + ERR_NOSUCHCHANNEL);
		else if ((itMap = chanMap.find(*it)) == chanMap.end())
		{
			itMap =	chanMap.insert(std::pair<std::string, Channel>(*it, Channel())).first;
			itMap->second.addChanOp(&client);
			if (itKey != keys.end())
				itMap->second.setPassword(*itKey);
			client.getChannels().push_back(*it);
			sendConfirm(client, cmds[0] + " " + *it, "");
			itMap->second.sendConfirmChan(client, cmds[0] + " " + *it, "");
		}
		else
		{
			if (!client.isInChan(*it))
			{
				if ((!itMap->second.getPassword().empty() && itKey == keys.end()) || itMap->second.getPassword() != *itKey)
				{
					sendMsg(client, "475", cmds[0],  *it + ERR_BADCHANNELKEY);
				}
				else
				{
					itMap->second.addClient(&client);
					client.getChannels().push_back(*it);
					sendConfirm(client, cmds[0] + " " + *it, "");
					itMap->second.sendConfirmChan(client, cmds[0] + " " + *it, "");
				}
			}
		}
		if (itKey != keys.end())
			itKey++;
	}
}
