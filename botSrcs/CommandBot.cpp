/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 22:27:57 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/04 17:34:55 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	Bot::command()
{
	cmdMap[std::string("PING")] = &Bot::pong; 
	cmdMap[std::string("INVITE")] = &Bot::invite; 
	cmdMap[std::string("PRIVMSG")] = &Bot::privmsg; 
	cmdBotMap[std::string("HELP")] = &Bot::help; 
	cmdBotMap[std::string("HELLO")] = &Bot::hello; 
	cmdBotMap[std::string("TIME")] = &Bot::timeCmd; 
	cmdBotMap[std::string("CALCUL")] = &Bot::calcul; 
}

void	Bot::pong(std::vector<std::string> cmds)
{
	std::string	message("PONG " + cmds[1] + "\r\n");
	sendMsg(message);
}

void	Bot::invite(std::vector<std::string> cmds)
{
	if (cmds[3][0] == ':')
		cmds[3].erase(0, 1);
	std::string	message("JOIN " + cmds[3] + "\r\n");
	
	sendMsg(message);
}

void	Bot::privmsg(std::vector<std::string> cmds)
{
	if (cmds[0][0] == ':')
		cmds[0].erase(0, 1);
	if (cmds[3][0] == ':')
		cmds[3].erase(0, 1);
	if (cmds[2][0] == '#')
		cmds[0].assign(cmds[2]);
	else
		cmds[0] = cmds[0].substr(0, cmds[0].find("!"));
	std::string	message("PRIVMSG " + cmds[0] + " :Unknow command, please use \"!BOT HELP\"\r\n");
	std::vector<std::string>	botCmds = ft_split(cmds[3], " ");
	std::transform(botCmds[0].begin(), botCmds[0].end(), botCmds[0].begin(), toupper);
	if (botCmds[0] != "!BOT" || botCmds.size() < 2)
	{
		if (cmds[2][0] != '#' || cmds[2] == "#bot" || cmds[2] == "#Bot")
			sendMsg(message);
		return ;
	}
	std::transform(botCmds[1].begin(), botCmds[1].end(), botCmds[1].begin(), toupper);
	std::map<std::string, pfunc>::iterator	itMap;
	itMap = cmdBotMap.find(botCmds[1]);
	if (itMap != cmdBotMap.end())
		CALL_MEMBER_FN(*this, itMap->second) (cmds);
	else
		sendMsg(message);
}

void	Bot::help(std::vector<std::string> cmds)
{
	std::string	message("PRIVMSG " + cmds[0] + " :HELP : !BOT <command> {HELLO, TIME, CALCUL}\r\n");
	sendMsg(message);
}

void	Bot::hello(std::vector<std::string> cmds)
{
	std::string	message("PRIVMSG " + cmds[0] + " :Hello, I am autoBot!\r\n");
	sendMsg(message);
}

void	Bot::timeCmd(std::vector<std::string> cmds)
{
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	std::string	message("PRIVMSG " + cmds[0] + " :Current Date Time : " + buf + "\r\n");
	sendMsg(message);
}

void	Bot::calcul(std::vector<std::string> cmds)
{
	std::vector<std::string>	botCmds = ft_split(cmds[3], " ");
	std::string	errMsg("PRIVMSG " + cmds[0] + " :CALCUL : !BOT CALCUL <number1> <operator> <number2> [ <operator> {+, -, *, /, %} ]\r\n");
	double	a, b = 0.0;

	if (botCmds.size() < 5)
	{
		sendMsg(errMsg);
		return ;
	}
	if (!isdigit(botCmds[2][0]) || !isdigit(botCmds[4][0]))
	{
		sendMsg(errMsg);
		return ;
	}
	a = atof(botCmds[2].c_str());
	b = atof(botCmds[4].c_str());
		std::cout << a << " " <<  b << std::endl;
	std::string message("PRIVMSG " + cmds[0] + " :RESULT : " + std::to_string(a) + " " + botCmds[3] + " " + std::to_string(b) + " = ");
	if (botCmds[3] == "+")
	{
		sendMsg(message + std::to_string(a + b) + "\r\n");
		return ;
	}
	else if (botCmds[3] == "-")
	{
		sendMsg(message + std::to_string(a - b) + "\r\n");
		return ;
	}
	else if (botCmds[3] == "*")
	{
		sendMsg(message + std::to_string(a * b) + "\r\n");
		return ;
	}
	else if (botCmds[3] == "/")
	{
		sendMsg(message + std::to_string(a / b) + "\r\n");
		return ;
	}
	else if (botCmds[3] == "%")
	{
		sendMsg(message + std::to_string((int)a % (int)b) + "\r\n");
		return ;
	}
	else
		sendMsg(errMsg);
}