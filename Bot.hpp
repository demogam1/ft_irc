/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:05:52 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/31 17:51:29 by asebrech         ###   ########.fr       */
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

# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

# include "defineBot.hpp"

class Bot
{
	public :

			Bot();
			Bot(int port, std::string const & pass, std::string const & IP);
			~Bot();

			void	init();
			void	run();


			std::vector<std::string>	splitCmd(std::string const & s, std::string const & seperator);
			void	cmdPars(std::string const & str);

	private :
	
			int	port;
			std::string	pass;
			std::string	IP;
			int sock;
			int client_fd;
			struct sockaddr_in serv_addr;
			std::string	buff;
};

#endif