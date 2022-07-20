/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 09:25:19 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 18:08:03 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <vector>
# include <string>

class	Client
{
	public:
			Client(int sd, char * IP, uint32_t port );
			~Client();

			int	getSocket() const;
			void setSocket(int sd);

			std::string	& getBuff();

			std::string	const & getIP() const;

			uint32_t	getPort() const;

			std::string	const & getNick() const;
			void	setNick(std::string const & val);

			std::string	const & getPass() const;
			void	setPass(std::string const & val);

			std::string	const & getUser() const;
			void	setUser(std::string const & val);

			std::string	const & getMode() const;
			void	setMode(std::string const & val);
			
			std::string	const & getUnused() const;
			void	setUnused(std::string const & val);

			std::string	const & getRealname() const;
			void	setRealname(std::string const & val);

			bool	getNicked() const;
			void	setNicked(bool val);

			bool	getUsered() const;
			void	setUsered(bool val);

			bool	getRegistered() const;
			void	setRegistered(bool val);

			bool	getbeDeleted() const;
			void	setbeDeleted(bool val);

			bool	getOperator() const;
			void	setOperator(bool val);

			std::vector<std::string>	okay;
	private:
			int	socket;
			std::string	IP;
			uint32_t port;
			std::string	buffer;
			std::string	nick;
			std::string	pass;
			std::string user;
			std::string mode;
			std::string unused;
			std::string realname;
			bool	nicked;
			bool	usered;
			bool	registered;
			bool	beDeleted;
			bool	Operator;
};

#endif
