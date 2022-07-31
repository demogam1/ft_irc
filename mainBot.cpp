/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainBot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:05:00 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/31 13:07:56 by asebrech         ###   ########.fr       */
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
		if (port < 1 || port > 65535)
		{
			std::cout << RED + "Error Port : must be an int between 1 and 65535" + RESET << std::endl;
			return (1);
		}
		Bot	bot(port, av[2], av[3]);
		autobot(bot);
	}
	else if (ac == 1)
	{
		Bot	bot;
		autobot(bot);
	}
	else
	{
		std::cout << YELLOW + "./bot <port> <pass> <IP>" + RESET << std::endl;
		return (1);
	}

	return (0);	
}