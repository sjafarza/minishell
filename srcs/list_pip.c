/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:43:10 by saray             #+#    #+#             */
/*   Updated: 2021/11/24 11:07:53 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_tok_pip	*ft_make_list_pip(t_tok_pip	*l)
{
	t_tok_pip	*head;

	head = (t_tok_pip *)malloc(sizeof(t_tok_pip));
	if (!head)
		return (NULL);
	head->cmd = NULL;
	head->next = NULL;
	//head->nb = 0;
	head->type = STATE_GENERAL;
	l = head;	
return (head);
}

void	ft_add_list_pip(t_tok_pip *head, char *s)
{
	t_tok_pip	*cur;
	t_tok_pip	*new;

	if (!head->cmd)
	{
		head->cmd = ft_strdup(s);
		head->type = STATE_GENERAL;
	}
	else
	{
		new = (t_tok_pip *)malloc(sizeof(t_tok_pip));
		new->cmd = ft_strdup(s);
		new->type = STATE_GENERAL;
		new->next = NULL;
		cur = head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}


void	ft_print_list_pip(t_tok_pip *head)
{
	t_tok_pip	*cur;

	cur = head;
	while (cur->next)
	{
		printf("iiiiiiiiciiiiiii print of list_pip\n");
		printf("*cur->data = %s\n",cur->cmd);
		cur = cur->next;
	}
		printf("*cur->data = %s\n",cur->cmd);
}
