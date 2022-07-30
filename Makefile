# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misaev <misaev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 14:07:04 by asebrech          #+#    #+#              #
#    Updated: 2022/07/28 17:10:16 by misaev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
NAME = ircserv 
SRC =	main.cpp \
		Server.cpp \
		Client.cpp \
		Command.cpp \
		Channel.cpp \
		pass.cpp \
		nick.cpp \
		user.cpp \
		quit.cpp \
		oper.cpp \
		mode.cpp \
		join.cpp \
		part.cpp \
		pong.cpp \
		kill.cpp \
		privmsg.cpp \
		away.cpp \
		notice.cpp \
		invite.cpp	\
		topic.cpp \
		names.cpp \

ifdef VERBOSEOFF
	CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -D VERBOSE=0
else
	CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -D VERBOSE=1
endif

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

verboseOff :
	@make VERBOSEOFF=1 all

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re verboseOff
