# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 09:42:54 by cwon              #+#    #+#              #
#    Updated: 2025/04/10 13:08:10 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
# CFLAGS = -Wall -Wextra -Werror
# for race condition checking
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

HEADER = philo.h
SRC = \
	init.c \
	mutex.c \
	parse.c \
	philo.c \
	routine_util.c \
	routine.c \
	thread.c \
	time.c \
	watchdog.c
MAIN = main.c
OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re