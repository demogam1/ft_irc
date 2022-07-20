/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:30:18 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 17:42:25 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

# include <vector> 

class	Channel
{
	public:

			Channel();
			~Channel();

			void	addClient(Client * Client);

	private:

			std::vector<Client *>	clients;
};

#endif
