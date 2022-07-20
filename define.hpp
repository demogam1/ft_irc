/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:52:06 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/20 09:24:50 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_HPP
# define DEFINE_HPP

# define CLIENT client.getNick() + "!" + client.getUser() + "@" + client.getIP()	

# define RPL_WELCOME ":Welcome to the ft_irc Internet Relay Network " + CLIENT
# define RPL_YOUREOPER ":You are now an IRC operator"

# define ERR_UNKNOWNCOMMAND ":Unknown command"
# define ERR_NONICKNAMEGIVEN ":No nickname given"
# define ERR_NICKNAMEINUSE ":Nickname is already in use"
# define ERR_ERRONEUSNICKNAME ":Erroneous nickname"
# define ERR_NOTREGISTERED ":You have not registered"
# define ERR_NEEDMOREPARAMS ":Not enough parameters"
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH ":Password incorrect"
# define ERR_NOOPERHOST ":No O-lines for your host"

#endif
