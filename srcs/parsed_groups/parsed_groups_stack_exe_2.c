/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_groups_stack_exe_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/27 14:29:33 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list_double	*find_next_of_type(t_list_double *parsed_group, int type)
{
	t_list_double		*parsed_group_it;
	t_cell_parsed_group	*tmp_cell;

	parsed_group_it = parsed_group;
	while (parsed_group_it->next)
	{
		tmp_cell = parsed_group_it->content;
		if (tmp_cell->type == type)
			return (parsed_group_it);
		parsed_group_it = parsed_group_it->next;
	}
	return (NULL);
}

int	fill_io_until_pipe(t_list_double *parsed_group, t_stack	*io_stack)
{
	t_cell_parsed_group	*tmp_cell;

	while (parsed_group)
	{
		tmp_cell = parsed_group->content;
		if (tmp_cell->type == TYPE_PIPE)
			break ;
		if (tmp_cell->type == TYPE_INPUT1 || tmp_cell->type == TYPE_INPUT2
			|| tmp_cell->type == TYPE_OUTPUT1 || tmp_cell->type == TYPE_OUTPUT2)
		{
			if (array_len((const char **)tmp_cell->args) != 2)
				return (-EXIT_FAILURE);
			add_back_io_stack(io_stack, tmp_cell->args[1], tmp_cell->type);
			tmp_cell->args[1] = NULL;
		}
		parsed_group = parsed_group->next;
	}
	return (EXIT_SUCCESS);
}

t_stack	gather_io(t_list_double *parsed_group)
{
	t_stack	result;

	result = (t_stack){0};
	if (fill_io_until_pipe(parsed_group, &result) != EXIT_SUCCESS)
	{
		clear_io_stack(&result);
		result = (t_stack){0};
		result.total_item = -1;
	}
	return (result);
}

static int	execute_parsed_groups_stack_int(t_env *env,
	t_list_double *parsed_group)
{
	char			**args;
	t_list_double	*next_pipe;

	if (!parsed_group)
		return (EXIT_SUCCESS);
	args = gather_splitted_args_for_cmd(parsed_group);
	if (!args)
		return (-EXIT_FAILURE);
	if (add_back_pipex_stack(env, args, gather_io(parsed_group))
		== -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	next_pipe = find_next_of_type(parsed_group, TYPE_PIPE);
	if (!next_pipe)
		return (EXIT_SUCCESS);
	execute_parsed_groups_stack_int(env, next_pipe->next);
	return (EXIT_SUCCESS);
}

int	execute_parsed_groups_stack(t_env *env)
{
	if (execute_parsed_groups_stack_int(env, env->parsed_groups_stack.head)
		== EXIT_SUCCESS && env->pipex_stack.total_item > 0)
	{
		clear_parsed_groups_stack(env);
		return (EXIT_SUCCESS);
	}
	clear_parsed_groups_stack(env);
	return (-EXIT_FAILURE);
}
