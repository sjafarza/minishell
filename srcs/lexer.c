/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:03:40 by saray             #+#    #+#             */
/*   Updated: 2021/11/20 18:48:40 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	ft_lexer(char *line)
{
	t_tok	*tok_head;
	t_lexer	lex;
	char	**cmd;
	int	i;
	
	printf("******in ft_lexer***********************************\n");
	cmd = ft_split(line,';');
	//ft_find_error(cmd);
	tok_head = ft_make_list(&lex);
	//tok_head = ft_make_nod(&lex);
	lex.nb_tok = 0;
	i = -1;
	while (cmd[++i])
	{
		printf("\nChek print of each cmd,tmp[%d]=%s\n", i, cmd[i]);
		ft_add_list(tok_head, cmd[i], &lex);
	}
	printf("\nprint list in fin lexer : \n");
	ft_print_list(lex.token);
	printf("\n lex.nb_tok = %d \n", lex.nb_tok);
	printf("*******fin of ft_lexer*****************************\n\n");
	return (1);
}
