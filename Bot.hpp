/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:05:52 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/03 18:33:12 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <time.h>

# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include <map>

# include "defineBot.hpp"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class Bot
{
	typedef void (Bot::*pfunc)(std::vector<std::string>);
	public :

			Bot();
			Bot(int port, std::string const & pass, std::string const & IP);
			~Bot();

			void	init();
			void	run();

			std::vector<std::string>	ft_split(std::string const & s, std::string const & seperator);
			std::vector<std::string>	splitCmd(std::string const & s, std::string const & seperator);
			void	cmdPars(std::string const & str);

			void	command();
			void	invite(std::vector<std::string> cmds);
			void	privmsg(std::vector<std::string> cmds);

			void	hello(std::vector<std::string> cmds);
			void	timeCmd(std::vector<std::string> cmds);

	private :
	
			int	port;
			std::string	pass;
			std::string	IP;
			int sock;
			int client_fd;
			struct sockaddr_in serv_addr;
			std::string	buff;
			int	isRegistered;
			std::map<std::string, pfunc>	cmdMap;
			std::map<std::string, pfunc>	cmdBotMap;
};

#endif