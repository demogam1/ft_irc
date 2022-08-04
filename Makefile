# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asebrech <asebrech@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 14:07:04 by asebrech          #+#    #+#              #
#    Updated: 2022/08/04 11:28:43 by asebrech         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = clang++
VERBOSE = 1
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -D VERBOSE=$(VERBOSE)
NAME = ircserv 
SRC =	srcs/main.cpp \
		srcs/Server.cpp \
		srcs/Client.cpp \
		srcs/Command.cpp \
		srcs/Channel.cpp \
		srcs/pass.cpp \
		srcs/nick.cpp \
		srcs/user.cpp \
		srcs/quit.cpp \
		srcs/oper.cpp \
		srcs/mode.cpp \
		srcs/join.cpp \
		srcs/part.cpp \
		srcs/pong.cpp \
		srcs/kill.cpp \
		srcs/privmsg.cpp \
		srcs/away.cpp \
		srcs/notice.cpp \
		srcs/invite.cpp	\
		srcs/topic.cpp \
		srcs/names.cpp \
		srcs/list.cpp \

OBJ = $(SRC:.cpp=.o)

SRCBOT =	botSrcs/mainBot.cpp \
			botSrcs/Bot.cpp \
			botSrcs/CommandBot.cpp \

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
