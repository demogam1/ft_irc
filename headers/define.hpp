/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:52:06 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/0 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DEFINE_HPP
# define DEFINE_HPP

# define CLIENT client.getNick() + "!" + client.getUser() + "@" + client.getIP()
# define TERMINATOR terminator.getNick() + "!" + terminator.getUser() + "@" + terminator.getIP()

# define RPL_WELCOME ":Welcome to the ft_IRC Internet Relay Network " + CLIENT
# define RPL_YOUREOPER ":You are now an IRC operator"
# define RPL_UNAWAY ":You are no longer marked as being away"
# define RPL_NOWAWAY ":You have been marked as being away"
# define RPL_NOTOPIC ":No topic is set"
# define RPL_ENDOFWHOIS ":End of WHOIS list"
# define RPL_ENDOFWHO ":End of WHO list"
# define RPL_WHOISIDLE " :seconds idle"

# define ERR_NOSUCHCHANNEL ":No such channel"
# define ERR_NOTONCHANNEL " :You're not on that channel"
# define ERR_USERONCHANNEL ":is already on channel"
# define ERR_INVITEONLYCHAN " :Cannot join channel (+i)"
# define ERR_BADCHANNELKEY " :Cannot join channel (+k)"
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
# define ERR_CHANOPRIVSNEEDED ":You're not channel operator"
# define ERR_USERNOTINCHANNEL ":They aren't on that channel"
# define ERR_NOSUCHSERVER ":No such server"
# define ERR_NOORIGIN ":No origin specified"
# define ERR_UNKNOWNMODE ":is unknown mode char to me for "


# define RED	std::string("\e[31m")
# define GREEN	std::string("\e[32m")
# define YELLOW	std::string("\e[33m")
# define BLUE	std::string("\e[94m")
# define MAGENTA std::string("\e[35m")
# define UNDER	std::string("\e[4m")
# define RESET	std::string("\e[0m")

#endif
