# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 16:06:44 by tcharuel          #+#    #+#              #
#    Updated: 2024/01/17 16:50:13 by tcharuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_FILES = main.c parsing.c simulation.c philosopher.c lock_operations.c log.c timestamp.c

CC = cc
CFLAGS = -g3 -Wextra -Wall -Werror
RM = rm -f

$(NAME): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $(SRC_FILES) -lpthread

all: $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

valgrind: re
	valgrind --tool=helgrind -s ./philo 2 40 41 42 8

.PHONY: all clean fclean re
