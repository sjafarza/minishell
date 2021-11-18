# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:36:55 by saray             #+#    #+#              #
#    Updated: 2021/11/18 12:41:34 by saray            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell


CC = clang

CFLAGS = -Wall -Wextra -Werror

HEADER = ./inc/parser.h



SRC = ./srcs/main.c ./srcs/free.c ./srcs/lexer.c ./srcs/utils_list.c ./srcs/error.c

SRCB = ./srcs/lib/get_next_line.c ./srcs/lib/split.c ./srcs/lib/substr.c ./srcs/lib/strdup.c \
       ./srcs/lib/ft_memcmp.c ./srcs/lib/ft_strlen.c ./srcs/lib/ft_del_EmptySpace.c

OBJ = $(SRC:c=o) $(SRCB:c=o)


all: $(NAME)


$(NAME): $(OBJ)
	@echo "\033[0;32m\n\nCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n\033[0mDone !"


%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re bonus
