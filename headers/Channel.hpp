/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:30:18 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/06 18:40:33 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

# include "Client.hpp"
# include "define.hpp"

# include <vector> 
# include <iostream>
# include <string>
# include <ctime>


# include <sys/socket.h> 

class	Channel
{
	public:

			Channel();
			~Channel();

			void	addClient(Client * client);

			void	addChanOp(Client * client);

			void	deleteClient(Client * client);

			void	deleteChanOp(Client * client);
			void	addInvited(Client * client);

			void	deleteInvited(Client * Client);

			bool	isInvited(Client & client) const;

			void    sendConfirmChan(Client const & client, std::string const & cmd, std::string const & opt);

			bool	isChanOp(Client const & client);

			bool	getInvite();
			void 	setInvite(bool set);

			std::string	const & getTopic();
			void 	setTopic(std::string const & val, Client & client);
			
			void	enableTopic(bool val);
			bool	getEnableTopic();

			bool	chanEmpty() const;

			void	setPassword(std::string const & str);
			bool 	isPassOn() const;
			std::string const & getPassword(void) const;

			std::string getTopicAuthor();

	private:

			std::vector<Client *>	clients;
			std::vector<Client *>	chanOp;
			std::vector<Client *>	invited;
			bool		invite;
			bool		topicEnabled;
			bool		isPassword;
			std::string topicAuthor;
			std::string	topic;
			std::string	password;
};

#endif