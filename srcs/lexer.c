/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:03:40 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 13:06:24 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	ft_lexer(char *line)
{
	t_tok	*tok_head;
	t_lexer	lex;
	char	**cmd;
	char	**a_tok;
	int	i;
	int	j;
	
	printf("******in ft_lexer\n");
	cmd = ft_split(line,';');
	tok_head = ft_make_list(&lex);
	lex.nb_tok = 0;
	i = -1;
	//analise of each CMD
	while (cmd[++i])
	{
		printf("\nChek print of each cmd,tmp[%d]=%s\n", i, cmd[i]);
		a_tok = ft_split(cmd[i], ' ');
		if (!ft_find_error(a_tok))
		{
			j = -1;
			while (a_tok[++j])
				ft_add_list(tok_head, a_tok[j], &lex);
			printf("\nprint list : \n");
			ft_print_list(lex.token);
		}
	}
	printf("\n lex.nb_tok = %d \n", lex.nb_tok);
	printf("*******fin of ft_lexer\n\n");
	return (1);
}
