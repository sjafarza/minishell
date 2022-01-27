# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:36:55 by saray             #+#    #+#              #
#    Updated: 2022/01/27 14:40:26 by scarboni         ###   ########.fr        #
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

HEADER 		= ./inc/minishell.h ./inc/lib.h

MINILIB_PATH		= lib/
CMDS_PATH			= cmds/
DATAS_PATH			= datas/
IO_PATH				= io/
PARSED_GROUPS_PATH	= parsed_groups/
PIPEX_PATH			= pipex/
SRC_PATH			= ./srcs/
LIBFT_PATH			= libft/

BASE =		main.c \
			signal.c \

SRC_FILES		= $(BASE)

MINILIB = 	ft_strchr_index.c \
			ft_is_blank.c \
			ft_strcat.c \

SRC_FILES	+=	$(addprefix $(MINILIB_PATH), $(MINILIB))

CMDS 	 = 	bash_cmd.c \
			echo_cmd.c \
			exit_cmd.c \
			env_cmd.c \
			unset_cmd.c \
			export_cmd.c \
			pwd_cmd.c \
			cd_cmd.c \
			export_sans_arg_cmd.c \
			select_right_cmd.c

SRC_FILES	+=	$(addprefix $(CMDS_PATH), $(CMDS))

DATAS 	 = 	add_env_var.c \
			array_len.c \
			check_parsing.c \
			clean_env_vars.c \
			del_env_var.c \
			extract_parsed_groups.c \
			find_and_update_env_var.c \
			find_env_var.c \
			find_next_i.c \
			free_array.c \
			free_t_env.c \
			ft_is_valid_for_env_var_name.c \
			get_raw_env_array.c \
			init_cwd.c \
			init_empty_env_var.c \
			init_env_vars.c \
			init_path.c \
			init_t_str.c \
			is_sequence_equal_to_parser_code.c \
			parse_dollar.c \
			parse_line_1.c \
			parse_line_2.c \
			parse_quotes.c \
			parse_standard.c \
			parse_type_arg_1.c \
			parse_type_arg_2.c \
			print_vars.c \
			replace_in_str.c \
			replace_in_io.c \
			produce_name_value.c

SRC_FILES	+=	$(addprefix $(DATAS_PATH), $(DATAS))

PIPEX 	 = 	pipex_stack_exe.c \
			pipex_stack.c \
			print_pipex_stack.c

SRC_FILES	+=	$(addprefix $(PIPEX_PATH), $(PIPEX))

IO 	 = 				io_openers.c \
					io_stack_exe.c \
					io_stack.c \
					here_doc.c \
					substitute_line_env.c

SRC_FILES	+=	$(addprefix $(IO_PATH), $(IO))

PARSED_GROUPS 	 = 	parsed_groups_stack_exe_1.c \
					parsed_groups_stack_exe_2.c \
					parsed_groups_stack.c

SRC_FILES	+=	$(addprefix $(PARSED_GROUPS_PATH), $(PARSED_GROUPS))

SRC			= 	$(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ 		= 	$(addprefix $(OBJ_PATH), $(SRC_FILES:c=o))

OBJ_PATHS_INIT			=	$(addprefix $(OBJ_PATH), $(MINILIB_PATH) $(CMDS_PATH) $(DATAS_PATH) $(PIPEX_PATH) $(PARSED_GROUPS_PATH) $(IO_PATH))

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
