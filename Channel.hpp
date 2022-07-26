/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:30:18 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/26 15:51:07 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

# include "Client.hpp"
# include "define.hpp"

# include <vector> 

# include <iostream>

# include <sys/socket.h> 

class	Channel
{
	public:

			Channel();
			~Channel();

			void	addClient(Client * client);

			void	addChanOp(Client * client);

			void	deleteClient(Client * client);

			void    sendConfirmChan(Client const & client, std::string const & cmd, std::string const & opt);

			bool	isChanOp(Client const & client);

			bool	getInvite();
			void 	setInvite(bool set);

			std::string	const & getTopic();
			void 	setTopic(std::string const & topic);

			bool	chanEmpty() const;

	private:

			std::vector<Client *>	clients;
			std::vector<Client *>	chanOp;
			bool	invite;
			std::string	topic;
};

#endif