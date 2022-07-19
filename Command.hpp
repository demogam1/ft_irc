/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:05:58 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/13 16:52:52 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <list>
# include <iostream>
# include <algorithm>
# include <string>
# include <map>
# include <sys/socket.h>

# include "Client.hpp"
# include "utile.hpp"
# include "define.hpp"

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class	Command
{
	typedef void (Command::*pfunc)(std::vector<std::string>, Client &);
	public :

			Command(std::string const & pass, std::list<Client> & clients, std::string const & IP);
			~Command();

			void	sendMsg(Client const & client, std::string nb, std::string opt, std::string err);

			void	sendConfirm(Client const & client, std::vector<std::string> const & cmds);

			bool	isSpecial(char c) const;

			void	setIP(std::string const & val);

			void	parsCmd(Client & client);

			void	registerClient(Client & client);

			void	nick(std::vector<std::string> cmds, Client & client);

			void	user(std::vector<std::string> cmds, Client & client);
			
			void	pass(std::vector<std::string> cmds, Client & client);

			void	quit(std::vector<std::string> cmds, Client & client);

	private :

			std::string	password;
			std::list<Client> & clients;
			std::string	IP;
			std::map<std::string, pfunc>	cmdMap;
};

#endif
