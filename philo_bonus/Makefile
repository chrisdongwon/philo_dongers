# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 09:42:54 by cwon              #+#    #+#              #
#    Updated: 2025/04/22 22:45:59 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

HEADER = philo_bonus.h
SRC = \
	flush_bonus.c \
	init_bonus.c \
	parse_bonus.c \
	philo_bonus.c \
	semaphore_bonus.c
MAIN = main_bonus.c
OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

all: $(NAME)

bonus: all

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus