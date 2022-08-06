/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:58:40 by misaev            #+#    #+#             */
/*   Updated: 2022/08/06 20:11:10 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Command.hpp"

void Command::mode(std::vector<std::string> cmds, Client & client)
{
    int error_nbr = 0;
    int sign = '+';
    if (!client.getRegistered())
    {
        sendMsg(client, "451", "", ERR_NOTREGISTERED);
        return;
    }
    if (cmds.size() < 3)
    {
        sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
        return;
    }
    if (cmds[1][0] != '#')
    {
        if (cmds[1] != client.getNick())
        {
            sendMsg(client, "502", "", ERR_USERSDONTMATCH);
            return;
        }
        for (size_t i = 0;i < cmds[2].length(); i++)
        {
            if (cmds[2][i] == '-')
                sign = '-';
            else if (cmds[2][i] == '+')
                sign = '+';
            else if (cmds[2][i] == 'o')
            {
                if (sign == '-')
                {    
                    if(client.getOperator() == true)
                    {
                        client.setOperator(false);
                        sendSpecConfirm(client , client.getNick(), cmds[0], cmds[2]);
                    }
                }
            }
            else if (error_nbr == 0)
            {
                sendMsg(client, "501", "", ERR_UMODEUNKNOWNFLAG);
                error_nbr++;
            }
        }
    }
    else if (cmds[1][0] == '#')
    {
		std::string	arg("+");
		std::string	opt;
		bool	okay = false;
        std::map<std::string, Channel>::iterator	itMap;
        if ((itMap = chanMap.find(cmds[1])) != chanMap.end())
        {
            if (client.isInChan(cmds[1]) == true)
            {
                if(itMap->second.isChanOp(client) == true)
                {
                    for (size_t i = 0;i < cmds[2].length(); i++)
					{
						if (cmds[2][i] != '-' && cmds[2][i] != '+' && cmds[2][i] != 'o' && cmds[2][i] != 'i' && cmds[2][i] != 't' && cmds[2][i] != 'k')
                        {
							std::string s;
							s.push_back(cmds[2][i]);
                            sendMsg(client, "472", s, ERR_UNKNOWNMODE + itMap->first);
							return ;
                        }
					}
                    for (size_t i = 0;i < cmds[2].length(); i++)
                    {    
                        if (cmds[2][i] == '-' && sign != '-')
						{
                            sign = '-';
							arg.append("-");
						}
                        else if (cmds[2][i] == '+' && sign != '+')
						{
                            sign = '+';
							arg.append("+");
						}
                        else if (cmds[2][i] == 'o')
                        {
                            if (cmds.size() < 4)
                            {
                                sendMsg(client, "461", cmds[0], ERR_NEEDMOREPARAMS);
								continue ;
                            }
                            std::list<Client>::iterator	it = clients.begin();
                            for (; it != clients.end(); it++)
                                if (cmds[3] == it->getNick())
                                    break;
                            if (it == clients.end())
                            {
                                sendMsg(client, "401", "", ERR_NOSUCHNICK);
								continue ;
                            }
                            if (it->isInChan(cmds[1]) == true)
                            {                                
                                if (sign == '-')
                                {
                                    if (itMap->second.isChanOp(*it) == true)
                                    {
                                        itMap->second.deleteChanOp(&(*it));
										itMap->second.addClient(&(*it));
										arg.append("o");
										okay = true;
                                    }
                                }
                                else if (sign == '+')
                                {
                                    if (itMap->second.isChanOp(*it) == false)
                                    {
                                        itMap->second.addChanOp(&(*it));                                
										itMap->second.deleteClient(&(*it));
										arg.append("o");
										okay = true;
                                    }
                                }
                            }
                            else
                            {
                                sendMsg(client, "442", client.getNick() + " " +  cmds[3] + " " + cmds[1], ERR_USERNOTINCHANNEL);
								continue ;
                            }
                        }
                        else if (cmds[2][i] == 'i')
                        {
                            if (sign == '-')
                            {
                                if (itMap->second.getInvite() == true)
                                {
                                    itMap->second.setInvite(false);
									arg.append("i");
									okay = true;
                                }
                            }
                            if (sign == '+')
                            {                                
                                if (itMap->second.getInvite() == false)
                                {
                                    itMap->second.setInvite(true);
									arg.append("i");
									okay = true;
                                }
                            }
                        }
                        else if (cmds[2][i] == 't')
                        {
                            if (sign == '-')
                            {
                                if (itMap->second.getEnableTopic() == true)
                                {
                                    itMap->second.enableTopic(false);
									arg.append("t");
									okay = true;
                                }
                            }
                            else if (sign == '+')
                            {
                                if (itMap->second.getEnableTopic() == false)
                                {
                                    itMap->second.enableTopic(true);
									arg.append("t");
									okay = true;
                                }
                            }
                        }
                        else if (cmds[2][i] == 'k')
                        {
                            if (sign == '-')
                            {
                                if (cmds.size() == 4 && cmds[3] == itMap->second.getPassword())
                                {
                                    itMap->second.setPassword("");
									opt.assign("*");
									arg.append("k");
									okay = true;
                                }
                            }
                            else if (sign == '+')
                            {
                                if (cmds.size() == 4)
                                {
                                    itMap->second.setPassword(cmds[3]);
									opt.assign(cmds[3]);
									arg.append("k");
									okay = true;
                                }
                            }
                        }
                    }
					if (okay)
					{
						for (size_t i = 0; i < arg.length(); i++)
						{
							if ((i + 1) != arg.length() && (arg[i + 1] == '-' || arg[i + 1] == '+'))
								arg.erase(i, 1);
						}
						for (int i = arg.length() - 1; i != 0; i--)
						{
							if (arg[i] == '-' || arg[i] == '+')
								arg.erase(i, 1);
							else
								break;
						}
						if (opt.empty())
						{
							sendConfirm(client , cmds[0] + " " + cmds[1] + " " + arg, "");
							itMap->second.sendConfirmChan(client, cmds[0] + " " + cmds[1] + " " + arg, "");	
						}
						else
						{
							sendConfirm(client , cmds[0]  + " " + cmds[1] + " " + arg + " " + opt, "");
							itMap->second.sendConfirmChan(client, cmds[0] + " " + cmds[1] + " " + arg + " " + opt, "");	
						}
					}
                }
                else
                {
                    sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
                    return;
                }
            }
            else if (client.isInChan(cmds[1]) == false)
            {
                sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
                return;
            }
        }
        else
        {
            sendMsg(client, "482", cmds[1], ERR_CHANOPRIVSNEEDED);
            return;
        }
    }
    return;
}