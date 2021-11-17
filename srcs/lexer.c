/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:03:40 by saray             #+#    #+#             */
/*   Updated: 2021/11/17 11:17:21 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_lexer(char *line)
{
	t_tok	*tok_head;
	t_lexer	lex;
	char	**cmd;
	char	**a_tok;
	int	i;
	
	tok_head = ft_make_list(&lex);
	lex.nb_tok = 0;
	printf("******in ft_lexer\n");
	cmd = ft_split(line,';');
	i = -1;
	//analise of each CMD
	while (cmd[++i])
	{
		printf("\nChek print of each cmd,tmp[%d]=%s\n", i, cmd[i]);
		a_tok = ft_split(cmd[i], ' ');
		int j = -1;
		while (a_tok[++j])
			ft_add_list(tok_head, a_tok[j], &lex);
		printf("\nprint list : \n");
		ft_print_list(lex.token);
	}
	printf("\n lex.nb_tok = %d \n", lex.nb_tok);
	printf("*******fin of ft_lexer\n\n");

}
