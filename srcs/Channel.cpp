/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:29:35 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/06 18:40:39 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel() : invite(false),topicEnabled(false),isPassword(false), topic(""), password("") {}

Channel::~Channel() {}

void Channel::addClient(Client *client)
{
	clients.push_back(client);
}

void Channel::addChanOp(Client *client)
{
	chanOp.push_back(client);
}

void Channel::deleteClient(Client *client)
{
	std::vector<Client *>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (client == *it)
		{
			clients.erase(it);
			return;
		}
	}
	for (it = chanOp.begin(); it != chanOp.end(); it++)
	{
		if (client == *it)
		{
			chanOp.erase(it);
			return;
		}
	}
}

void Channel::deleteChanOp(Client *client)
{
	std::vector<Client *>::iterator it;
	for (it = chanOp.begin(); it != chanOp.end(); it++)
	{
		if (client == *it)
		{
			chanOp.erase(it);
			return;
		}
	}
}

void	Channel::addInvited(Client *client)
{
	invited.push_back(client);
}

void	Channel::deleteInvited(Client * client)
{
	std::vector<Client *>::iterator it;
	for (it = invited.begin(); it != invited.end(); it++)
	{
		if (client == *it)
		{
			invited.erase(it);
			return;
		}
	}
}

bool	Channel::isInvited(Client & client) const
{
	std::vector<Client *>::const_iterator it = invited.begin();
	for (; it != invited.end(); it++)
		if (*it == &client)
			return true;
	return false;
}

void	Channel::sendConfirmChan(Client const &client, std::string const &cmd, std::string const &opt)
{
	std::string message(":" + CLIENT);
	if (opt.empty())
		message += " " + cmd + "\r\n";
	else
		message += " " + cmd + " :" + opt + "\r\n";
	std::vector<Client *>::iterator it = clients.begin();
	for (; it != clients.end(); it++)
	{
		if (*it != &client)
		{
			send((*it)->getSocket(), message.c_str(), message.length(), 0);
			if (VERBOSE)
			{
				std::cout << "Command replied, socket fd : " << (*it)->getSocket() << ", IP : " << (*it)->getIP() << ", port : " << (*it)->getPort() << std::endl;
				std::cout << GREEN + ">> " + message + RESET;
			}
		}
	}
	for (it = chanOp.begin(); it != chanOp.end(); it++)
	{
		if (*it != &client)
		{
			send((*it)->getSocket(), message.c_str(), message.length(), 0);
			if (VERBOSE)
			{
				std::cout << "Command replied, socket fd : " << (*it)->getSocket() << ", IP : " << (*it)->getIP() << ", port : " << (*it)->getPort() << std::endl;
				std::cout << GREEN + ">> " + message + RESET;
			}
		}
	}
}

bool Channel::isChanOp(Client const &client)
{
	std::vector<Client *>::iterator it = chanOp.begin();
	for (; it != chanOp.end(); it++)
		if (*it == &client)
			return true;
	return false;
}

bool Channel::chanEmpty() const
{
	return (clients.empty() && chanOp.empty());
}

bool Channel::getInvite() { return (invite); }

void Channel::setInvite(bool set) { invite = set; }

std::string const & Channel::getTopic() { return (topic); }

void Channel::setTopic(std::string const & val, Client & client) 
{
	std::time_t result = std::time(nullptr);
	topic = val;
	topicAuthor.assign(CLIENT + " " + std::to_string((int)result));
}

void Channel::setPassword(std::string const &str) { password = str, isPassword = true; }
bool Channel::isPassOn() const {return (isPassword); }
std::string const & Channel::getPassword(void) const { return (password); }

void  Channel::enableTopic(bool val) { topicEnabled = val; }

bool Channel::getEnableTopic() { return (topicEnabled); }

std::string Channel::getTopicAuthor() {return (topicAuthor);}
