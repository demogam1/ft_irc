/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:50:48 by asebrech          #+#    #+#             */
/*   Updated: 2022/08/07 16:00:33 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void	irc(Server & server)
{
	try
	{
		server.init();
		server.run();
	}
	catch (std::exception & e)
	{
		std::cerr << RED + "exception caught: " << e.what() + RESET << std::endl;
	}
}

int	main(int ac, char **av)
{
	int	port = 0;

	if (ac == 3)
	{
		port = atoi(av[1]);
		if (port < 1024 || port > 65535)
		{
			std::cout << RED + "Error Port : must be an int between 1024 and 65535" + RESET << std::endl;
			return (1);
		}
		Server	server(port, av[2]);
		irc(server);
	}
	else
	{
		std::cout << YELLOW + "./ircserv <port> <password>" + RESET << std::endl;
		return (1);
	}

	return (0);
}
