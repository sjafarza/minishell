/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_groups_stack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/25 23:12:27 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cell_parsed_groups(void *v_cell)
{
	t_cell_parsed_group	*cell;

	cell = (t_cell_parsed_group *)v_cell;
	if (cell->args)
		free_array(cell->args);
	free(cell);
}

void	clear_parsed_groups_stack(t_env *env)
{
	ft_lstdbclear(&env->parsed_groups_stack.head, &free_cell_parsed_groups);
	env->parsed_groups_stack.total_item = 0;
	env->parsed_groups_stack.tail = NULL;
}

int	add_back_parsed_groups_stack(t_env *env, char **args, int type)
{
	t_cell_parsed_group	*content;

	if (!args || !args[0])
		return (-EXIT_FAILURE);
	content = (t_cell_parsed_group *)malloc(sizeof(t_cell_parsed_group));
	if (!content)
		return (-EXIT_FAILURE);
	content->args = args;
	content->type = type;
	env->parsed_groups_stack.tail = ft_lstdbnew(content);
	if (!env->parsed_groups_stack.tail)
	{
		free(content);
		return (-EXIT_FAILURE);
	}
	ft_lstdbadd_back(&env->parsed_groups_stack.head,
		env->parsed_groups_stack.tail);
	env->parsed_groups_stack.total_item++;
	return (EXIT_SUCCESS);
}

static void	print_parsed_group_stack_int(void *v_content)
{
	int					i;
	t_cell_parsed_group	*content;

	content = (t_cell_parsed_group *)v_content;
	i = 0;
	printf("PRINT CELL TYPE %d:\n", content->type);
	while (content->args[i])
	{
		printf("%d[%s]\n", i, content->args[i]);
		i++;
	}
}

void	print_parsed_group_stack(t_env *env)
{
	printf("        parsed_group stack, size : %d\n",
		env->parsed_groups_stack.total_item);
	if (env->parsed_groups_stack.head)
		ft_lstdbiter_fun_first(env->parsed_groups_stack.head,
			&print_parsed_group_stack_int);
	printf("        End parsed_group stack : %d\n",
		env->parsed_groups_stack.total_item);
}
