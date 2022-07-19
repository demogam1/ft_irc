/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:27:10 by asebrech          #+#    #+#             */
/*   Updated: 2022/07/12 09:05:19 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utile.hpp"

std::vector<std::string> split(const std::string & s, const std::string & seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
		if (s[prev_pos] == ':' && prev_pos != 0)
		{
        	std::string substring( s.substr(prev_pos) );
        	output.push_back(substring);
			return (output);
		}
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

		if (!substring.empty())
        	output.push_back(substring);

		pos += seperator.length();
        prev_pos = pos;
    }

	std::string substring( s.substr(prev_pos, pos-prev_pos) );
	if (!substring.empty())
		output.push_back(substring);

    return output;
}
