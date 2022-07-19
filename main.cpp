/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:50:48 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/19 19:09:37 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main()
{
	Server	server;
	std::cout << "otot\n";
	try
	{
		server.init();
		server.run();
	}
	catch (std::exception & e)
	{
		std::cerr << "exception caught: " << e.what() << std::endl;
	}
	return (0);
}
