/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2021/12/02 10:06:34 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./lib.h"
# include "../libft/libft.h"

#define PATH_STR "PATH"
#define PATH_LEN 4

/* ************************************************************************** */
/* 									ENV					    				  */
/* ************************************************************************** */

typedef struct s_str{
	char	*str;
	int		len;
}t_str;

typedef struct s_env_var {
	t_str	name;
	t_str	value;
} t_env_var;

typedef struct s_cell_parsed_group{
	char	**args;
	int		type;
} t_cell_parsed_group;

typedef struct s_cell_pipex
{
	char	**args;
}	t_cell_pipex;

typedef struct s_stack
{
	t_list_double	*head;
	t_list_double	*tail;
	int				total_item;
}	t_stack;


typedef struct s_env {
	t_env_var	*env_vars;
	int			env_vars_max;
	char		**paths;
	char		*cwd;
	t_stack		pipex_stack;
	t_stack		parsed_groups_stack;
} t_env; 


/* ************************************************************************** */
/* 									CMDS 									  */
/* ************************************************************************** */
#define ID_BASH_CMD	0
#define ID_ECHO		1
#define ID_CD		2
#define ID_PWD		3
#define ID_EXPORT	4
#define ID_UNSET	5
#define ID_ENV		6
#define ID_EXIT		7

#define CODE_ECHO		"echo"
#define LEN_ECHO		4
#define CODE_CD			"cd"
#define LEN_CD			2
#define CODE_PWD		"pwd"
#define LEN_PWD			3
#define CODE_EXPORT		"export"
#define LEN_EXPORT		6
#define CODE_UNSET		"unset"
#define LEN_UNSET		5
#define CODE_ENV		"env"
#define LEN_ENV			3
#define CODE_EXIT		"exit"
#define LEN_EXIT		4
#define MAX_CMD			8

typedef struct s_cell
{
	char	**args;
}	t_cell;

typedef struct s_cmd{
	t_str	code;
	int		(*fun)(t_env *env, const char *cmd, const char **args);
} t_cmd;

int		mock_cmd(t_env *env, const char *cmd, const char **args);
int		echo_cmd(t_env *env, const char *cmd, const char **args);
int		exit_cmd(t_env *env, const char *cmd, const char **args);
int		env_cmd(t_env *env, const char *cmd, const char **args);
int		unset_cmd(t_env *env, const char *cmd, const char **args);
int		export_cmd(t_env *env, const char *cmd, const char **args);
int		bash_cmd(t_env *env, const char *cmd, const char **args);
int		select_right_cmd(t_env *env, const char *cmd, const char** args);

static const t_cmd g_cmd_dictionary[MAX_CMD] = {
	(t_cmd){(t_str){"", 0}, &bash_cmd},
	(t_cmd){(t_str){CODE_ECHO, LEN_ECHO}, &echo_cmd},
	(t_cmd){(t_str){CODE_CD, LEN_CD}, &mock_cmd},
	(t_cmd){(t_str){CODE_PWD, LEN_PWD}, &mock_cmd},
	(t_cmd){(t_str){CODE_EXPORT, LEN_EXPORT}, &export_cmd},
	(t_cmd){(t_str){CODE_UNSET, LEN_UNSET}, &unset_cmd},
	(t_cmd){(t_str){CODE_ENV, LEN_ENV}, &env_cmd},
	(t_cmd){(t_str){CODE_EXIT, LEN_EXIT}, &exit_cmd}
};

/* ************************************************************************** */
/* 									PARSER 									  */
/* ************************************************************************** */

typedef struct s_line
{
	char	**line;
	int		*i;
} t_line;

typedef struct s_tmp_parsed
{
	char	***arg;
	int		ac;
	int		*type;
	int		start;
	int		*high_level_start;
} t_tmp_parsed;

typedef struct s_parser{
	t_str	code;
	int		(*fun)(t_line *, t_tmp_parsed *, int *, int);	
} t_parser;

int		parse_back_slash(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_type_wa(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_type_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_type_w1a_only(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);
int		parse_type(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i);

#define PARSE_CUT				45
#define PARSE_INCOMPLETE		48
#define SET_TYPE_WITHOUT_ARGS	43
#define SET_TYPE				42
#define TYPE_INPUT2				0
#define TYPE_OUTPUT2			1
#define TYPE_PIPE				2
#define TYPE_INPUT1				3
#define TYPE_OUTPUT1			4
#define TYPE_BACK_SLASH			5
#define TYPE_DOUBLE_QUOTE		6
#define TYPE_QUOTE				7
#define TYPE_CMD				8
#define MAX_PARSER				8
#define START_AUTHORISED_W1A	5

static const t_parser g_parser_dictionary[MAX_PARSER] = {
	(t_parser){(t_str){"<<", 2}, &parse_type_wa},
	(t_parser){(t_str){">>", 2}, &parse_type_w1a},
	(t_parser){(t_str){"|", 1}, &parse_type_wa},
	(t_parser){(t_str){"<", 1}, &parse_type_w1a_only},
	(t_parser){(t_str){">", 1}, &parse_type_w1a},
	(t_parser){(t_str){"\\", 1}, &parse_back_slash},
	(t_parser){(t_str){"\"", 1}, &parse_double_quote},
	(t_parser){(t_str){"\'", 1}, &parse_simple_quote}
};

/* ************************************************************************** */
/* 									DATAS  									  */
/* ************************************************************************** */

#define INCOMPLETE_PATTERN -2

void		clean_env_vars(t_env *env);
int			find_and_update_env_var(t_env *env, char *var_name, char* new_value);
t_env_var	*find_env_vars_t_str(t_env *env, t_str var);
t_env_var	*find_env_vars(t_env *env, char* var_name);
void		free_array(char **arr);
void		free_t_env(t_env *env);
int			init_cwd(t_env *env);
int			init_env_vars(t_env *env, char **raw_env);
int			init_path(t_env *env);
void		print_vars(t_env *env);
int			init_t_str(t_str *obj, char* s);
int			replace_in_str(t_env *env, char **str);
int			replace_in_str_until_i(t_env *env, char **str, int max_i);
int			extract_parsed_groups(t_env *env, char **line);
int			is_not_valid(char c);
int			is_valid(char c);
int			go_to_next_needed_i(char *line, int(*keep_going)(char), int i);
int			del_env_var(t_env   *env, char  *var_name);
int			fill_tmp(t_env *env, t_env *tmp, char *var_name, int i);
int			init_str(t_str *obj, char *s);
int			add_env_var(t_env *env, char *var);
int			dup_tmp_to_env(t_env *env, t_env *tmp, int i);

/* ************************************************************************** */
/* 									PIPEX  									  */
/* ************************************************************************** */

void	clear_pipex_stack(t_env *env);
int		add_back_pipex_stack(t_env *env, char **args);
void	print_pipex_stack(t_env *env);
void	execute_pipex_stack(t_env *env);

/* ************************************************************************** */
/* 									PARSED_GROUPS							  */
/* ************************************************************************** */

void	execute_parsed_groups_stack(t_env *env);
void	clear_parsed_groups_stack(t_env *env);
int	add_back_parsed_groups_stack(t_env *env, char **args, int type);
void	print_parsed_group_stack(t_env *env);

/* ************************************************************************** */
/* 									LIB   									  */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, size_t len_mx);
int	ft_strchr_index(const char *s, int c);
int	ft_strchr_index_until_i(const char *s, int c, int i_max);

/* ************************************************************************** */
/* 									SIG  									  */
/* ************************************************************************** */

void	ft_sig_handler(int sig);

#endif
