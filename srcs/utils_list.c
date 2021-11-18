/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:43:10 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 10:32:39 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	ft_type(char *s)
{
	int	i;

	//parser s
	i = -1;
	while (s[++i]);	
	//in case error managment of exit clean
	return (1);
}

t_tok	*ft_make_list(t_lexer *lex)
{
	t_tok	*head;

	head = malloc(sizeof(t_tok));
	head->data = NULL;
	head->type = STATE_GENERAL;
	head->next = NULL;
	lex->token = head;
	return (head);
}

void	ft_add_list(t_tok *head, char *s, t_lexer *lex)
{
	t_tok	*cur;
	t_tok	*new;

	if (lex->nb_tok == 0)
	{
		head->data = ft_strdup(s);
	//	head->type = ft_type(s);
	}
	else
	{
		new = (t_tok *)malloc(sizeof(t_tok));
		new->data = ft_strdup(s);
		//new->type = ft_type(s);
		new->next = NULL;
		cur = head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	lex->nb_tok += 1;
}
	
void	ft_print_list(t_tok *head)
{
	t_tok	*cur;

	printf("*head->data = %s\n",head->data);
	cur = head->next;
	while (cur)
	{
		printf("*cur->data = %s\n",cur->data);
		cur = cur->next;
	}
}
