# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:36:55 by saray             #+#    #+#              #
#    Updated: 2021/11/27 21:37:07 by scarboni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= minishell
MAKE_LIBFT			=	makelibft
LIBFTPATH			=	libft/
LIBFT_AR			=	libft.a

OBJ_PATH	= bin/

CC 			= clang

CFLAGS 		= -W -Wall -Wextra -Werror -g3 -pedantic

LDFLAGS		=	-L$(LIBFTPATH) -lft  -lreadline

HEADER 		= ./inc/parser.h

MINILIB_PATH		= lib/
CMDS_PATH			= cmds/
DATAS_PATH			= datas/
SRC_PATH			= ./srcs/
LIBFT_PATH			= libft/

BASE =		main.c \
			free.c \
			lexer.c \
			list.c \
			list_pip.c \
			error.c \
			signal.c \

SRC_FILES		= $(BASE)

MINILIB = 	ft_strchr_index.c \
			ft_is_blank.c \
			ft_del_EmptySpace.c

SRC_FILES	+=	$(addprefix $(MINILIB_PATH), $(MINILIB))

CMDS 	 = 	bash_cmd.c \
			mock_cmd.c \
			select_right_cmd.c

SRC_FILES	+=	$(addprefix $(CMDS_PATH), $(CMDS))

DATAS 	 = 	clean_env_vars.c \
			find_env_var.c \
			init_env_vars.c \
			init_path.c \
			print_vars.c \
			init_t_str.c \
			replace_in_str.c

SRC_FILES	+=	$(addprefix $(DATAS_PATH), $(DATAS))

SRC			= 	$(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ 		= 	$(addprefix $(OBJ_PATH), $(SRC_FILES:c=o))

OBJ_PATHS_INIT			=	$(addprefix $(OBJ_PATH), $(MINILIB_PATH) $(CMDS_PATH) $(DATAS_PATH))

all: $(OBJ_PATHS_INIT) $(MAKE_LIBFT)  $(NAME)

$(LIBFT_PATH)	:
	git clone https://github.com/Psycokwet/libft.git  $(LIBFT_PATH)

$(MAKE_LIBFT)		: $(LIBFT_PATH)
	@$(MAKE) -C    $(LIBFT_PATH) $(BONUS)

$(OBJ_PATHS_INIT)	:
	@echo "\033[0;33mGenerating bin folder and subfolders"
	@mkdir -p  $@  

$(NAME): $(OBJ) $(addprefix $(LIBFTPATH),$(LIBFT_AR))
	@echo "\033[0;32m\n\nCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)  
	@echo "\n\033[0mDone !"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADERS_FILES)
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@${CC} ${CFLAGS}   -c $< -o $@ 

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\033[0m"
	$(MAKE) -C $(LIBFT_PATH) clean	

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"
	$(MAKE) -C $(LIBFT_PATH) fclean				

re: fclean all

.PHONY: clean fclean re bonus
