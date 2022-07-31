/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:05:52 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/31 14:01:52 by asebrech         ###   ########.fr       */
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

# include "defineBot.hpp"

class Bot
{
	public :

			Bot();
			Bot(int port, std::string const & pass, std::string const & IP);
			~Bot();

			void	init();

			void	run();

	private :
	
			int	port;
			std::string	pass;
			std::string	IP;
			int sock;
			int valread;
			int client_fd;
			struct sockaddr_in serv_addr;
			char buffer[1024];
};

#endif