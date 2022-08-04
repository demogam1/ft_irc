/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBot.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 22:27:57 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/04 11:57:37 by asebrech         ###   ########.fr       */
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
	cmdBotMap[std::string("SEXY")] = &Bot::sexy; 
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
	std::string	message("PRIVMSG " + cmds[0] + " :HELP : !BOT <command> {HELLO, TIME, CALCUL, SEXY}\r\n");
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
	std::string message("PRIVMSG " + cmds[0] + " :RESULT : " + botCmds[2] + " " + botCmds[3] + " " + botCmds[4] + " = ");
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

void	Bot::sexy(std::vector<std::string> cmds)
{
	std::vector<std::string>	sexy;

	sexy.push_back("                         8888  8888888");
	sexy.push_back("                  888888888888888888888888");
	sexy.push_back("               8888:::8888888888888888888888888");
	sexy.push_back("             8888::::::8888888888888888888888888888");
	sexy.push_back("            88::::::::888:::8888888888888888888888888");
	sexy.push_back("          88888888::::8:::::::::::88888888888888888888");
	sexy.push_back("        888 8::888888::::::::::::::::::88888888888   888");
	sexy.push_back("           88::::88888888::::m::::::::::88888888888    8");
	sexy.push_back("         888888888888888888:M:::::::::::8888888888888");
	sexy.push_back("        88888888888888888888::::::::::::M88888888888888");
	sexy.push_back("        8888888888888888888888:::::::::M8888888888888888");
	sexy.push_back("         8888888888888888888888:::::::M888888888888888888");
	sexy.push_back("        8888888888888888::88888::::::M88888888888888888888");
	sexy.push_back("      88888888888888888:::88888:::::M888888888888888   8888");
	sexy.push_back("     88888888888888888:::88888::::M::;o*M*o;888888888    88");
	sexy.push_back("    88888888888888888:::8888:::::M:::::::::::88888888    8");
	sexy.push_back("   88888888888888888::::88::::::M:;:::::::::::888888888");
	sexy.push_back("  8888888888888888888:::8::::::M::aAa::::::::M8888888888       8");
	sexy.push_back("  88   8888888888::88::::8::::M:::::::::::::888888888888888 8888");
	sexy.push_back(" 88  88888888888:::8:::::::::M::::::::::;::88:88888888888888888");
	sexy.push_back(" 8  8888888888888:::::::::::M::\"@@@@@@\"::::8w8888888888888888");
	sexy.push_back("  88888888888:888::::::::::M:::::\"@a@\":::::M8i8888888888888888");
	sexy.push_back(" 8888888888::::88:::::::::M88:::::::::::::M88z88888888888888888");
	sexy.push_back("8888888888:::::8:::::::::M88888:::::::::MM888!888888888888888888");
	sexy.push_back("888888888:::::8:::::::::M8888888MAmmmAMVMM888*88888888   88888888");
	sexy.push_back("888888 M:::::::::::::::M888888888:::::::MM88888888888888   8888888");
	sexy.push_back("8888   M::::::::::::::M88888888888::::::MM888888888888888    88888");
	sexy.push_back(" 888   M:::::::::::::M8888888888888M:::::mM888888888888888    8888");
	sexy.push_back("  888  M::::::::::::M8888:888888888888::::m::Mm88888 888888   8888");
	sexy.push_back("   88  M::::::::::::8888:88888888888888888::::::Mm8   88888   888");
	sexy.push_back("   88  M::::::::::8888M::88888::888888888888:::::::Mm88888    88");
	sexy.push_back("   8   MM::::::::8888M:::8888:::::888888888888::::::::Mm8     4");
	sexy.push_back("       8M:::::::8888M:::::888:::::::88:::8888888::::::::Mm    2");
	sexy.push_back("      88MM:::::8888M:::::::88::::::::8:::::888888:::M:::::M");
	sexy.push_back("     8888M:::::888MM::::::::8:::::::::::M::::8888::::M::::M");
	sexy.push_back("    88888M:::::88:M::::::::::8:::::::::::M:::8888::::::M::M");
	sexy.push_back("   88 888MM:::888:M:::::::::::::::::::::::M:8888:::::::::M:");
	sexy.push_back("   8 88888M:::88::M:::::::::::::::::::::::MM:88::::::::::::M");
	sexy.push_back("     88888M:::88::M::::::::::*88*::::::::::M:88::::::::::::::M");
	sexy.push_back("    888888M:::88::M:::::::::88@@88:::::::::M::88::::::::::::::M");
	sexy.push_back("    888888MM::88::MM::::::::88@@88:::::::::M:::8::::::::::::::*8");
	sexy.push_back("    88888  M:::8::MM:::::::::*88*::::::::::M:::::::::::::::::88@@");
	sexy.push_back("    8888   MM::::::MM:::::::::::::::::::::MM:::::::::::::::::88@@");
	sexy.push_back("     888    M:::::::MM:::::::::::::::::::MM::M::::::::::::::::*8");
	sexy.push_back("     888    MM:::::::MMM::::::::::::::::MM:::MM:::::::::::::::M");
	sexy.push_back("      88     M::::::::MMMM:::::::::::MMMM:::::MM::::::::::::MM");
	sexy.push_back("       88    MM:::::::::MMMMMMMMMMMMMMM::::::::MMM::::::::MMM");
	sexy.push_back("        88    MM::::::::::::MMMMMMM::::::::::::::MMMMMMMMMM");
	sexy.push_back("         88   8MM::::::::::::::::::::::::::::::::::MMMMMM");
	sexy.push_back("          8   88MM::::::::::::::::::::::M:::M::::::::MM");
	sexy.push_back("              888MM::::::::::::::::::MM::::::MM::::::MM");
	sexy.push_back("             88888MM:::::::::::::::MMM:::::::mM:::::MM");
	sexy.push_back("             888888MM:::::::::::::MMM:::::::::MMM:::M");
	sexy.push_back("            88888888MM:::::::::::MMM:::::::::::MM:::M");
	sexy.push_back("           88 8888888M:::::::::MMM::::::::::::::M:::M");
	sexy.push_back("           8  888888 M:::::::MM:::::::::::::::::M:::M:");
	sexy.push_back("              888888 M::::::M:::::::::::::::::::M:::MM");
	sexy.push_back("             888888  M:::::M::::::::::::::::::::::::M:M");
	sexy.push_back("             888888  M:::::M:::::::::@::::::::::::::M::M");
	sexy.push_back("             88888   M::::::::::::::@@:::::::::::::::M::M");
	sexy.push_back("            88888   M::::::::::::::@@@::::::::::::::::M::M");
	sexy.push_back("           88888   M:::::::::::::::@@::::::::::::::::::M::M");
	sexy.push_back("          88888   M:::::m::::::::::@::::::::::Mm:::::::M:::M");
	sexy.push_back("          8888   M:::::M:::::::::::::::::::::::MM:::::::M:::M");
	sexy.push_back("         8888   M:::::M:::::::::::::::::::::::MMM::::::::M:::M");
	sexy.push_back("        888    M:::::Mm::::::::::::::::::::::MMM:::::::::M::::M");
	sexy.push_back("      8888    MM::::Mm:::::::::::::::::::::MMMM:::::::::m::m:::M");
	sexy.push_back("     888      M:::::M::::::::::::::::::::MMM::::::::::::M::mm:::M");
	sexy.push_back("  8888       MM:::::::::::::::::::::::::MM:::::::::::::mM::MM:::M:");
	sexy.push_back("             M:::::::::::::::::::::::::M:::::::::::::::mM::MM:::Mm");
	sexy.push_back("            MM::::::m:::::::::::::::::::::::::::::::::::M::MM:::MM");
	sexy.push_back("            M::::::::M:::::::::::::::::::::::::::::::::::M::M:::MM");
	sexy.push_back("           MM:::::::::M:::::::::::::M:::::::::::::::::::::M:M:::MM");
	sexy.push_back("           M:::::::::::M88:::::::::M:::::::::::::::::::::::MM::MMM");
	sexy.push_back("           M::::::::::::8888888888M::::::::::::::::::::::::MM::MM");
	sexy.push_back("           M:::::::::::::88888888M:::::::::::::::::::::::::M::MM");
	sexy.push_back("           M::::::::::::::888888M:::::::::::::::::::::::::M::MM");
	sexy.push_back("           M:::::::::::::::88888M:::::::::::::::::::::::::M:MM");
	sexy.push_back("           M:::::::::::::::::88M::::::::::::::::::::::::::MMM");
	sexy.push_back("           M:::::::::::::::::::M::::::::::::::::::::::::::MMM");
	sexy.push_back("           MM:::::::::::::::::M::::::::::::::::::::::::::MMM");
	sexy.push_back("            M:::::::::::::::::M::::::::::::::::::::::::::MMM");
	sexy.push_back("            MM:::::::::::::::M::::::::::::::::::::::::::MMM");
	sexy.push_back("             M:::::::::::::::M:::::::::::::::::::::::::MMM");
	sexy.push_back("             MM:::::::::::::M:::::::::::::::::::::::::MMM");
	sexy.push_back("              M:::::::::::::M::::::::::::::::::::::::MMM");
	sexy.push_back("              MM:::::::::::M::::::::::::::::::::::::MMM");
	sexy.push_back("               M:::::::::::M:::::::::::::::::::::::MMM");
	sexy.push_back("               MM:::::::::M:::::::::::::::::::::::MMM");
	sexy.push_back("                M:::::::::M::::::::::::::::::::::MMM");
	sexy.push_back("                MM:::::::M::::::::::::::::::::::MMM");
	sexy.push_back("                 MM::::::M:::::::::::::::::::::MMM");
	sexy.push_back("                 MM:::::M:::::::::::::::::::::MMM");
	sexy.push_back("                  MM::::M::::::::::::::::::::MMM");
	sexy.push_back("                  MM:::M::::::::::::::::::::MMM");
	sexy.push_back("                   MM::M:::::::::::::::::::MMM");
	sexy.push_back("                   MM:M:::::::::::::::::::MMM");
	sexy.push_back("                    MMM::::::::::::::::::MMM");
	sexy.push_back("                    MM::::::::::::::::::MMM");
	sexy.push_back("                     M:::::::::::::::::MMM");
	sexy.push_back("                    MM::::::::::::::::MMM");
	sexy.push_back("                    MM:::::::::::::::MMM");
	sexy.push_back("                    MM::::M:::::::::MMM:");
	sexy.push_back("                    mMM::::MM:::::::MMMM");
	sexy.push_back("                     MMM:::::::::::MMM:M");
	sexy.push_back("                     mMM:::M:::::::M:M:M");
	sexy.push_back("                      MM::MMMM:::::::M:M");
	sexy.push_back("                      MM::MMM::::::::M:M");
	sexy.push_back("                      mMM::MM::::::::M:M");
	sexy.push_back("                       MM::MM:::::::::M:M");
	sexy.push_back("                       MM::MM::::::::::M:m");
	sexy.push_back("                       MM:::M:::::::::::MM");
	sexy.push_back("                       MMM:::::::::::::::M:");
	sexy.push_back("                       MMM:::::::::::::::M:");
	sexy.push_back("                       MMM::::::::::::::::M");
	sexy.push_back("                       MMM::::::::::::::::M");
	sexy.push_back("                       MMM::::::::::::::::Mm");
	sexy.push_back("                        MM::::::::::::::::MM");
	sexy.push_back("                        MMM:::::::::::::::MM");
	sexy.push_back("                        MMM:::::::::::::::MM");
	sexy.push_back("                        MMM:::::::::::::::MM");
	sexy.push_back("                        MMM:::::::::::::::MM");
	sexy.push_back("                         MM::::::::::::::MMM");
	sexy.push_back("                         MMM:::::::::::::MM");
	sexy.push_back("                         MMM:::::::::::::MM");
	sexy.push_back("                         MMM::::::::::::MM");
	sexy.push_back("                          MM::::::::::::MM");
	sexy.push_back("                          MM::::::::::::MM");
	sexy.push_back("                          MM:::::::::::MM");
	sexy.push_back("                          MMM::::::::::MM");
	sexy.push_back("                          MMM::::::::::MM");
	sexy.push_back("                           MM:::::::::MM");
	sexy.push_back("                           MMM::::::::MM");
	sexy.push_back("                           MMM::::::::MM");
	sexy.push_back("                            MM::::::::MM");
	sexy.push_back("                            MMM::::::MM");
	sexy.push_back("                            MMM::::::MM");
	sexy.push_back("                             MM::::::MM");
	sexy.push_back("                             MM::::::MM");
	sexy.push_back("                              MM:::::MM");
	sexy.push_back("                              MM:::::MM:");
	sexy.push_back("                              MM:::::M:M");
	sexy.push_back("                              MM:::::M:M");
	sexy.push_back("                              :M::::::M:");
	sexy.push_back("                             M:M:::::::M");
	sexy.push_back("                            M:::M::::::M");
	sexy.push_back("                           M::::M::::::M");
	sexy.push_back("                          M:::::M:::::::M");
	sexy.push_back("                         M::::::MM:::::::M");
	sexy.push_back("                         M:::::::M::::::::M");
	sexy.push_back("                         M;:;::::M:::::::::M");
	sexy.push_back("                         M:m:;:::M::::::::::M");
	sexy.push_back("                         MM:m:m::M::::::::;:M");
	sexy.push_back("                          MM:m::MM:::::::;:;M");
	sexy.push_back("                           MM::MMM::::::;:m:M");
	sexy.push_back("                            MMMM MM::::m:m:MM");
	sexy.push_back("                                  MM::::m:MM");
	sexy.push_back("                                   MM::::MM");
	sexy.push_back("                                    MM::MM");
	sexy.push_back("                                     MMMM	");

	std::vector<std::string>::iterator	it;
	for (it = sexy.begin(); it != sexy.end(); it++)
	{
		usleep(300);
		sendMsg("PRIVMSG " + cmds[0] + " :" + MAGENTA + *it + RESET + "\r\n");
		usleep(300);
	}
}