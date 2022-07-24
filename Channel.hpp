/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:30:18 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/24 15:39:34 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

# include "Client.hpp"
# include "define.hpp"

# include <vector> 

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

			bool	chanEmpty() const;

	private:

			std::vector<Client *>	clients;
			std::vector<Client *>	chanOp;
};

#endif