/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:55:47 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/13 10:15:20 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>
# include <unistd.h>

# include <stdexcept>
# include <iostream>
# include <string>
# include <list>
# include <vector>

# include "Client.hpp"
# include "Command.hpp"

class	Server
{
	public:
			Server();
			~Server();

			void	myhostname();
			void	init();
			void	run();

	private:
			int	port;
			std::string	pass;
			std::string	IP;
			std::list<Client>	clients;
			Command	command; 

			int	master_socket;
			struct sockaddr_in address;
			int	addrlen;
			fd_set	readfds;
};

#endif
