/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:13:55 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/04 14:46:45 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

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
	std::vector<std::string>	chans = ft_split(cmds[1], ",");
	std::vector<std::string>	keys;
	std::vector<std::string>	names;
	names.push_back("names");
	names.push_back(cmds[1]);
	if (cmds.size() > 2)
		keys = ft_split(cmds[2], ",");
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
			Command::names(names, client);
			itMap->second.sendConfirmChan(client, cmds[0] + " " + *it, "");
		}
		else
		{
			if (!client.isInChan(*it))
			{
				if (!itMap->second.getPassword().empty() && (itKey == keys.end() || itMap->second.getPassword() != *itKey))
				{
					sendMsg(client, "475", *it + ERR_BADCHANNELKEY, "");
				}
				else if (itMap->second.getInvite() && !itMap->second.isInvited(client))
				{
					sendMsg(client, "473", *it + ERR_INVITEONLYCHAN, "");
				}
				else
				{
					itMap->second.addClient(&client);
					client.getChannels().push_back(*it);
					sendConfirm(client, cmds[0] + " " + *it, "");
					Command::names(names, client);
					if (!itMap->second.getTopic().empty())
					{
						sendMsg(client, "332", *it, itMap->second.getTopic());
						sendMsg(client, "333", *it, itMap->second.getTopicAuthor());
					}
					itMap->second.sendConfirmChan(client, cmds[0] + " " + *it, "");
				}
			}
		}
		if (itKey != keys.end())
			itKey++;
	}
}
