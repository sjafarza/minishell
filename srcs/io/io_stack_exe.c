/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_stack_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/23 21:46:21 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	execute_io_stack_int(t_env *env, t_list_double *io_node)
{
	int			id_io_type_action;
	t_cell_io	*io_cell;

	id_io_type_action = 0;
	if (!io_node)
		return (EXIT_SUCCESS);
	io_cell = io_node->content;
	if (!io_cell)
		return (-EXIT_FAILURE);
	while (id_io_type_action < MAX_IO_TYPES && g_io_opener_dictionary[id_io_type_action].type != io_cell->type)
		id_io_type_action++;
	if (g_io_opener_dictionary[id_io_type_action].type != io_cell->type
		|| g_io_opener_dictionary[id_io_type_action].fun(io_cell)
			== -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (execute_io_stack_int(env, io_node->next));
}

int	execute_io_stack(t_env *env, t_stack *io_stack)
{
	if (execute_io_stack_int(env, io_stack->head) == EXIT_SUCCESS)
	{
		clear_io_stack(io_stack);
		return (EXIT_SUCCESS);
	}
	clear_io_stack(io_stack);
	//close every fd opened
	return (-EXIT_FAILURE);
}
