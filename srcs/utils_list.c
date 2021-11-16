/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:43:10 by saray             #+#    #+#             */
/*   Updated: 2021/11/16 14:53:00 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

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

void	ft_add_list(char *s, t_lexer *lex)
{
	t_tok	*cur;
	t_tok	*new_tok;

	cur = lex->token;
	while (!cur)
		cur = cur->next;
	new_tok = malloc(sizeof(t_tok));
	new_tok = NULL;
	cur->data = ft_strdup(s);
	if (!(cur->data))
	{
		printf("\nError in malloc\n");
               //manage of free
	       //return ;
	}
	lex->nb_tok += 1;
	cur->next = new_tok;
}
	
void	ft_print_list(t_tok *head)
{
	t_tok	*cur;

	cur = head;
	printf("head in p_list = %s\n", head->data);
	while (cur)
	{
		printf("*cur->data = %s\n",cur->data);
		cur = cur->next;
	}
}

/*static t_lstnum	*add_num_to_struct(t_stack *a, long long num)
{
	t_lstnum	*new_num;

	if (num > INT_MAX || num < INT_MIN)
		free_a_error(a);
	new_num = (t_lstnum *)ft_memalloc(sizeof(t_lstnum));
	new_num->n = num;
	new_num->next = NULL;
	return (new_num);
}

static void	lst_addend(t_lstnum **backtrack, t_lstnum *new_num)
{
	t_lstnum	*tmp;

	if (*backtrack == NULL)
		return ;
	tmp = *backtrack;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_num;
	tmp = tmp->next;
	tmp->prev = *backtrack;
	*backtrack = tmp;
}

static void	add_nb_to_list(t_stack *s, t_lstnum *new_num, char *str, int *i)
{
	while (str[*i])
	{
		while (ft_isblank(str[*i]))
			(*i)++;
		if (str[*i] == '\0')
			break ;
		if (!ft_isdigit(str[*i]) && !ft_isblank(str[*i])
			&& str[*i] != '-' && str[*i] != '+' && str[*i] != '\0')
			free_a_error(s);
		if (ft_isdigit(str[*i]) && !ft_isdigit(str[*i + 1])
			&& !ft_isblank(str[*i + 1]) && str[*i + 1] != '\0')
			free_a_error(s);
		if ((str[*i] == '-' || str[*i] == '+')
			&& !ft_isdigit(str[*i + 1]) && str[*i + 1] != '\0')
			free_a_error(s);
		new_num = add_num_to_struct(s, ft_atoill(&str[*i]));
		lst_addend(&s->end, new_num);
		if (str[*i] == '-' || str[*i] == '+')
			(*i)++;
		while (ft_isdigit(str[*i]))
			(*i)++;
		if (str[*i] && !ft_isblank(str[*i]))
			free_a_error(s);
	}
}

void	parse_nb_from_first_str(t_stack *a, char *str)
{
	int			i;
	t_lstnum	*new_num;

	new_num = NULL;
	i = 0;
	if (!str)
		return ;
	while (ft_isblank(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
		free_a_error(a);
	a->head->n = ft_atoill(&str[i]);
	if (a->head->n > INT_MAX || a->head->n < INT_MIN)
		free_a_error(a);
	a->end = a->head;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] && !ft_isblank(str[i]))
		free_a_error(a);
	add_nb_to_list(a, new_num, str, &i);
}

void	parse_nb_from_second_str(t_stack *a, char *str)
{
	int			i;
	t_lstnum	*new_num;

	new_num = NULL;
	i = 0;
	if (!str)
		return ;
	add_nb_to_list(a, new_num, str, &i);
}


void	build_stack(t_stack *a, int ac, char **av)
{
	int			i;

	i = 2;
	a->head = ft_memalloc(sizeof(t_lstnum));
	parse_nb_from_first_str(a, av[1]);
	while (i < ac)
	{
		parse_nb_from_second_str(a, av[i]);
		i++;
	}
	if (!(check_double(a)))
	{
		free_a(a);
		ft_error();
	}
}*/
