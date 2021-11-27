# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:36:55 by saray             #+#    #+#              #
#    Updated: 2021/11/27 12:32:13 by scarboni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

OBJ_PATH	= bin/

CC 			= clang

CFLAGS 		= -W -Wall -Wextra -Werror -g3 -pedantic

HEADER 		= ./inc/parser.h

MINILIB_PATH		= lib/
CMDS_PATH			= cmds/
SRC_PATH			= ./srcs/

BASE =		main.c \
			free.c \
			lexer.c \
			list.c \
			list_pip.c \
			error.c \
			signal.c \

SRC_FILES		= $(BASE)

MINILIB = 	split.c \
			substr.c \
			strdup.c \
      		ft_strncmp.c \
      		ft_memcmp.c \
			ft_strlen.c \
			ft_del_EmptySpace.c

SRC_FILES	+=	$(addprefix $(MINILIB_PATH), $(MINILIB))

CMDS 	 = 	bash_cmd.c \
			mock_cmd.c \
			select_right_cmd.c


SRC_FILES	+=	$(addprefix $(CMDS_PATH), $(CMDS))

SRC			= 	$(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ 		= 	$(addprefix $(OBJ_PATH), $(SRC_FILES:c=o))

OBJ_PATHS_INIT			=	$(addprefix $(OBJ_PATH), $(MINILIB_PATH) + $(CMDS_PATH))

all: $(OBJ_PATHS_INIT) $(NAME)


$(OBJ_PATHS_INIT)	:
	@echo "\033[0;33mGenerating bin folder and subfolders"
	@mkdir -p  $@  

$(NAME): $(OBJ)
	@echo "\033[0;32m\n\nCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
	@echo "\n\033[0mDone !"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADERS_FILES)
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: clean fclean re bonus
