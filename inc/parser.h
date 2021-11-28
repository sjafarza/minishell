/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2021/11/28 17:05:22 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

static char *g_test_line = NULL;

/* ************************************************************************** */
/* 									CMDS 									  */
/* ************************************************************************** */

typedef struct s_str{
	char	*str;
	int		len;
} t_str;

typedef struct s_cmd{
	t_str	code;
	int		(*fun)(const char* cmd, const char** args);
} t_cmd;

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



typedef struct s_env_var {
	t_str	name;
	t_str	value;
} t_env_var;

typedef struct s_env {
	t_env_var	*env_vars;
	int			env_vars_max;
	char		**paths;
} t_env;

int		mock_cmd(const char *cmd, const char **args);
int		bash_cmd(const char *cmd, const char **args);
int		select_right_cmd(t_env *env, const char *cmd, const char** args);

static const t_cmd g_cmd_dictionary[MAX_CMD] = {
	(t_cmd){(t_str){"", 0}, &bash_cmd},
	(t_cmd){(t_str){CODE_ECHO, LEN_ECHO}, &mock_cmd},
	(t_cmd){(t_str){CODE_CD, LEN_CD}, &mock_cmd},
	(t_cmd){(t_str){CODE_PWD, LEN_PWD}, &mock_cmd},
	(t_cmd){(t_str){CODE_EXPORT, LEN_EXPORT}, &mock_cmd},
	(t_cmd){(t_str){CODE_UNSET, LEN_UNSET}, &mock_cmd},
	(t_cmd){(t_str){CODE_ENV, LEN_ENV}, &mock_cmd},
	(t_cmd){(t_str){CODE_EXIT, LEN_EXIT}, &mock_cmd}
};

/* ************************************************************************** */
/* 									DATAS  									  */
/* ************************************************************************** */

void		clean_env_vars(t_env *env);
int			find_and_update_env_var(t_env *env, char *var_name, char* new_value);
t_env_var	*find_env_vars_t_str(t_env *env, t_str var);
t_env_var	*find_env_vars(t_env *env, char* var_name);
void		free_array(char **arr);
void		free_t_env(t_env *env);
int			init_env_vars(t_env *env, char **raw_env);
int			init_path(t_env *env);
void		print_vars(t_env *env);
int			init_t_str(t_str *obj, char* s);
int			replace_in_str(t_env *env, char **str);
int			replace_in_str_until_i(t_env *env, char **str, int max_i);

/* ************************************************************************** */
/* 									LIB   									  */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, size_t len_mx);
int	ft_strchr_index(const char *s, int c);
int	ft_strchr_index_until_i(const char *s, int c, int i_max);



enum TokenType
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,

	TOKEN	= -1,
};

enum 
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

/*typedef struct s_sig
{
	pid_t	pid;
	int	error;
	int	status;
	int	test;
}	t_sig;*/

pid_t	g_pid;


typedef struct	s_tok
{
	char				*data;
	int					type;
	int					pip;
	int					nb_pip;
	struct s_tok_pip	*cmd_pip;
	struct s_tok		*next;
} t_tok;

typedef struct	s_tok_pip
{
	char				*cmd;
	int					type;
	//int					nb;
	struct s_tok_pip	*next;
} t_tok_pip;

typedef struct s_lexer
{
		struct s_tok	*token;
		int				nb_tok;
}	t_lexer;

void    ft_free(char    **a_env, char   **a_path);
int	ft_lexer(char *line);
int	ft_serch_pip(char *cmd);
void	ft_sig_handler(int sig);



/*
 ** list
 */

t_tok   *ft_make_list();
t_tok_pip	*ft_make_list_pip(t_tok_pip	*l);
void    ft_add_list(t_tok *head, char *s, t_lexer *lex);
void	ft_add_list_pip(t_tok_pip *head, char *s);
void    ft_print_list(t_tok *head);
void	ft_print_list_pip(t_tok_pip *head);
t_tok	*ft_make_nod(char *s, t_tok_pip	*t_pip_head);


/*
 ** error
 */
int     ft_find_error(char *line);
int	ft_find_quotes(char *line);
int	ft_quotes_is_paire(char *line);
int	ft_line_is_vide(char *s);
#endif
