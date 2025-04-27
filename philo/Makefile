# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 22:10:18 by cwon              #+#    #+#              #
#    Updated: 2025/04/27 20:45:49 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
# for race condition checking
#CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

HEADER = philo.h
SRC = \
	flush.c \
	init.c \
	mutex.c \
	parse.c \
	philo_util.c \
	philo.c \
	routine_util.c \
	routine.c \
	thread.c \
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