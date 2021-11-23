/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2021/11/22 10:28:03 by saray            ###   ########.fr       */
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
# include "./lib.h"


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
int    ft_serch_pip(char *cmd);
void    ft_sig_handler(int sig);




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
int     ft_find_error(char **line);
#endif
