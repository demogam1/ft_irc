/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainBot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:05:00 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/07 16:00:47 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

void	autobot(Bot & bot)
{
	try
	{
		bot.init();
		bot.run();
	}
	catch (std::exception & e)
	{
		std::cerr << RED + "exception caught: " << e.what() + RESET << std::endl;
	}
}

int	main(int ac, char **av)
{
	int	port = 0;
	
	if (ac == 4)
	{
		port = atoi(av[1]);
		if (port < 1024 || port > 65535)
		{
			std::cout << RED + "Error Port : must be an int between 1024 and 65535" + RESET << std::endl;
			return (1);
		}
		Bot	bot(port, av[2], av[3]);
		autobot(bot);
	}
	else
	{
		std::cout << YELLOW + "./bot <port> <pass> <IP>" + RESET << std::endl;
		return (1);
	}

	return (0);	
}