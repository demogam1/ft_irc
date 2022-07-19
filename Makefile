# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misaev <misaev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 14:07:04 by asebrech          #+#    #+#              #
#    Updated: 2022/07/19 18:14:55 by misaev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = a.out 
SRC =	main.cpp \
		Server.cpp \
		Client.cpp \
		Command.cpp \
		utile.cpp \
		oper.cpp \

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
