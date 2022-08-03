# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misaev <misaev@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 14:07:04 by asebrech          #+#    #+#              #
#    Updated: 2022/08/02 14:52:25 by misaev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
VERBOSE = 1
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -D VERBOSE=$(VERBOSE)
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
		list.cpp \

OBJ = $(SRC:.cpp=.o)

SRCBOT =	mainBot.cpp \
			Bot.cpp \

OBJBOT = $(SRCBOT:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

bot : $(OBJBOT)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	@rm -rf $(OBJ)
	@rm -rf $(OBJBOT)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf bot

re : fclean all

.PHONY : all clean fclean re
