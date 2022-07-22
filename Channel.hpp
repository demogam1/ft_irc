/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:30:18 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 12:01:05 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "define.hpp"

# include <vector> 

# include <sys/socket.h> 

class	Channel
{
	public:

			Channel();
			~Channel();

			void	addClient(Client * Client);

			void	addChanOp(Client * Client);

			void    sendConfirmChan(Client const & client, std::string const & cmd, std::string const & opt);

			// void	sendConfirmChanTo(Client const & client, Client const & terminator, std::string const & cmd, std::string const & opt);

	private:

			std::vector<Client *>	clients;
			std::vector<Client *>	chanOp;
};

#endif