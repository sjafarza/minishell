/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/27 20:03:46 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cell_io(void *v_cell)
{
	t_cell_io	*cell;

	cell = (t_cell_io *)v_cell;
	if (cell->fd >= 0)
		close(cell->fd);
	if (cell->arg)
		free(cell->arg);
	free(cell);
}

void	clear_io_stack(t_stack *io_stack)
{
	ft_lstdbclear(&(io_stack->head), &free_cell_io);
	io_stack->total_item = 0;
	io_stack->tail = NULL;
}

int	add_back_io_stack(t_stack *io_stack, char *arg, int type)
{
	t_cell_io	*content;

	content = (t_cell_io *)malloc(sizeof(t_cell_io));
	if (!content)
	{
		free(content);
		return (-EXIT_FAILURE);
	}
	content->fd = -1;
	content->arg = arg;
	content->type = type;
	io_stack->tail = ft_lstdbnew(content);
	if (!io_stack->tail)
	{
		free(content);
		return (-EXIT_FAILURE);
	}
	ft_lstdbadd_back(&(io_stack->head), io_stack->tail);
	io_stack->total_item++;
	return (EXIT_SUCCESS);
}

static void	print_io_stack_int(void *v_content)
{
	t_cell_io	*content;

	content = (t_cell_io *)v_content;
	printf("PRINT CELL %s:%d\n", content->arg, content->type);
}

void	print_io_stack(t_stack *io_stack)
{
	printf("        IO stack, size : %d\n", io_stack->total_item);
	if (io_stack->head)
		ft_lstdbiter_fun_first(io_stack->head,
			&print_io_stack_int);
	printf("        End IO stack : %d\n", io_stack->total_item);
}
