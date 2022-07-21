/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:25:11 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/21 14:06:21 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int sd, char * IP, uint32_t port) : socket(sd), IP(IP), port(port),
				buffer(), nick("*"), pass(""), user("*"), mode("*"), unused("*"), realname("*"),
				nicked(false), usered(false), registered(false), beDeleted(false), Operator(false) {}

Client::~Client() {}

int	Client::getSocket() const { return(socket); }

void	Client::setSocket(int sd) { socket = sd; }

std::string & Client::getBuff() { return(buffer); }

std::string const & Client::getIP() const { return(IP); }

uint32_t	Client::getPort() const { return(port); }

std::string const & Client::getNick() const { return(nick); }
void	Client::setNick(std::string const & val) { nick = val; }

std::string const & Client::getPass() const { return(pass); }
void	Client::setPass(std::string const & val) { pass = val; }

std::string const & Client::getUser() const  { return(user); }
void	Client::setUser(std::string const & val) { user = val; }

std::string const & Client::getMode() const  { return(mode); }
void	Client::setMode(std::string const & val) { mode = val; }

std::string const & Client::getUnused() const  { return(unused); }
void	Client::setUnused(std::string const & val) { unused = val; }

std::string const & Client::getRealname() const  { return(realname); }
void	Client::setRealname(std::string const & val) { realname = val; }

bool	Client::getNicked() const { return(nicked); }
void	Client::setNicked(bool val) { nicked = val; }

bool	Client::getUsered() const { return(usered); }
void	Client::setUsered(bool val) { usered = val; }

bool	Client::getRegistered() const { return(registered); }
void	Client::setRegistered(bool val) { registered = val; }

bool	Client::getbeDeleted() const { return(beDeleted); }
void	Client::setbeDeleted(bool val) { beDeleted = val; }

bool	Client::getOperator() const { return(Operator); }
void	Client::setOperator(bool val) { Operator = val; }

std::vector<std::string>	& Client::getChannels() { return(channels); }

bool	Client::isInChan(std::string const & str) const
{
	std::vector<std::string>::const_iterator	it = channels.begin();
	for (; it != channels.end(); it++)
	{
		if (str == *it)
			return (true);	
	}
	return (false);
}
