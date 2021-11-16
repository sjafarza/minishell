/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:03:40 by saray             #+#    #+#             */
/*   Updated: 2021/11/16 14:29:32 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_lexer(char *line)
{
	t_tok	*tok_head;
	t_lexer	lex;
	char	**cmd;
	char	**a_tok;
	
	tok_head = ft_make_list(&lex);
	lex.nb_tok = 0;
//	token = malloc(sizeof(t_tok));
//	lex = malloc(sizeof(t_lexer));
//	token->data = NULL;
	printf("******in ft_lexer\n");
	cmd = ft_split(line,';');
	int i = -1;
	//analise of each CMD
	while (cmd[++i])
	{
		printf("\ntmp[%d]=%s\n", i, cmd[i]);
		a_tok = ft_split(cmd[i], ' ');
		int j=-1;
		while (a_tok[++j])
		{
			ft_add_list(a_tok[j], &lex);
			/*token->data = ft_strdup(a_tok[j]);
			if (!token->data)
			{
				printf("\nError in malloc\n");
				//manage of free
				return ;
			}
			++lex.nb_tok;
			printf("token->data = %s\n", token->data);*/
		}
		ft_print_list(lex.token);
	}
	printf("\n lex.nb_tok = %d \n", lex.nb_tok);
	printf("*******fin of ft_lexer\n\n");

}

	
