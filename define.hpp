/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:52:06 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/22 15:41:39 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINE_HPP
# define DEFINE_HPP

# define CLIENT client.getNick() + "!" + client.getUser() + "@" + client.getIP()
# define TERMINATOR terminator.getNick() + "!" + terminator.getUser() + "@" + terminator.getIP()

# define RPL_WELCOME ":Welcome to the ft_irc Internet Relay Network " + CLIENT
# define RPL_YOUREOPER ":You are now an IRC operator"
# define RPL_UNAWAY ":You are no longer marked as being away"
# define RPL_NOWAWAY ":You have been marked as being away"

# define ERR_NOSUCHCHANNEL " :No such channel"
# define ERR_NOTONCHANNEL " :You're not on that channel"
# define ERR_UNKNOWNCOMMAND ":Unknown command"
# define ERR_NONICKNAMEGIVEN ":No nickname given"
# define ERR_NICKNAMEINUSE ":Nickname is already in use"
# define ERR_ERRONEUSNICKNAME ":Erroneous nickname"
# define ERR_NOTREGISTERED ":You have not registered"
# define ERR_NEEDMOREPARAMS ":Not enough parameters"
# define ERR_ALREADYREGISTRED ":Unauthorized command (already registered)"
# define ERR_PASSWDMISMATCH ":Password incorrect"
# define ERR_NOOPERHOST ":No O-lines for your host"
# define ERR_UMODEUNKNOWNFLAG ":Unknown MODE flag"
# define ERR_USERSDONTMATCH ":Cannot change mode for other users"
# define ERR_NOORIGIN ":No origin specified"
# define ERR_NOSUCHSERVICE ":No such service"
# define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator"
# define ERR_NOSUCHNICK ":No such nick/channel"
# define ERR_NORECIPIENT ":No recipient given (PRIVMSG)"
# define ERR_NOTEXTTOSEND ":No text to send"
# define ERR_CANNOTSENDTOCHAN ":Cannot send to channel"

#endif
