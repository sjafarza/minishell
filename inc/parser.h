/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 10:26:39 by saray            ###   ########.fr       */
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


typedef struct	s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
} t_tok;

typedef struct s_lexer
{
		struct s_tok	*token;
		int				nb_tok;
}	t_lexer;

void    ft_free(char    **a_env, char   **a_path);
int	ft_lexer(char *line);

/*
 ** list
 */

t_tok   *ft_make_list();
void    ft_add_list(t_tok *head, char *s, t_lexer *lex);
void    ft_print_list(t_tok *head);

/*
 ** error
 */
int     ft_find_error(char **line);
#endif
