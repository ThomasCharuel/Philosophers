# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 16:06:44 by tcharuel          #+#    #+#              #
#    Updated: 2024/01/21 10:20:24 by tcharuel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_FILES = main.c log.c timestamp.c philosopher.c simulation.c parsing.c

CC = cc
CFLAGS = -Wextra -Wall -Werror
RM = rm -f

$(NAME): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $(SRC_FILES) -lpthread

all: $(NAME)

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
