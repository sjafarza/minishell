/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:43:10 by saray             #+#    #+#             */
/*   Updated: 2021/11/26 11:03:56 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	ft_serch_pip(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '|')
			return (1);
	}
	return (0);
}

void	ft_list_pip(char *s, t_tok *tok, t_tok_pip *t_pip_head)
{
	char	**tmp;
	int		i;

	tok->pip = 1;
	t_pip_head = ft_make_list_pip(tok->cmd_pip);
	tmp = ft_split(s, '|');
	i = -1;
	while (tmp[++i])
		ft_add_list_pip(t_pip_head, tmp[i]);
	tok->pip += (i - 1);
	tok->cmd_pip = t_pip_head;
}

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

	head = (t_tok *)malloc(sizeof(t_tok));
	head->data = NULL;
	head->type = STATE_GENERAL;
	head->next = NULL;
	head->pip = 0;
	head->nb_pip = 0;
	head->cmd_pip = NULL;
	lex->token = head;
	return (head);
}

t_tok	*ft_make_nod(char *s, t_tok_pip	*t_pip_head)
{
	t_tok	*new;

	new = (t_tok *)malloc(sizeof(t_tok));
	if (!new)
		return (NULL);
	new->data = ft_strdup(s);
	new->type = STATE_GENERAL;
	new->next = NULL;
	new->cmd_pip = NULL;
	if (ft_serch_pip(s))
		ft_list_pip(s, new, t_pip_head);
	//new->type = ft_type(s);
	return (new);
}

void	ft_add_list(t_tok *head, char *s, t_lexer *lex)
{
	t_tok		*cur;
	t_tok		*new;
	t_tok_pip	*t_pip_head;

	t_pip_head = NULL;
	if (lex->nb_tok == 0)
	{
		head->data = ft_strdup(s);
		if (ft_serch_pip(s))
			ft_list_pip(s, head, t_pip_head);
	}
	else
	{
		new = ft_make_nod(s, t_pip_head);
		cur = head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	lex->nb_tok += 1;
}

void    ft_print_list_pip(t_tok_pip *head);
	
void	ft_print_list(t_tok *head)
{
	t_tok	*cur;
	
	cur = head;
	while (cur->next)
	{
		if (cur->pip)
			ft_print_list_pip(cur->cmd_pip);
		else
			printf("*cur->data = %s\n", cur->data);
		cur = cur->next;
	}
		if (cur->pip)
			ft_print_list_pip(cur->cmd_pip);
		else
			printf("*cur->data = %s\n",cur->data);
}
