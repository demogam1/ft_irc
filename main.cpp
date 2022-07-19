/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:50:48 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/19 19:18:26 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	main()
{
	Server	server;
	// asdasdas 
	//asdasdsa
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
