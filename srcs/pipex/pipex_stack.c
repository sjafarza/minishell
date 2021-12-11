/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/12/03 16:40:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cell_pipex(void *v_cell)
{
	t_cell_pipex *cell;

	cell = (t_cell_pipex*)v_cell;
	if (cell->args)
		free_array(cell->args);
	free(cell);
}

void	clear_pipex_stack(t_env *env)
{
	ft_lstdbclear(&env->pipex_stack.head, &free_cell_pipex);
	env->pipex_stack.total_item = 0;
	env->pipex_stack.tail = NULL;
}

int	add_back_pipex_stack(t_env *env, char **args)
{
	t_cell_pipex	*content;

	if (!args || !args[0])
		return (-EXIT_FAILURE);
	content = (t_cell_pipex *)malloc(sizeof(t_cell_pipex));
	if (!content)
		return (-EXIT_FAILURE);
	content->args = args;
	env->pipex_stack.tail = ft_lstdbnew(content);
	if (!env->pipex_stack.tail)
		return (-EXIT_FAILURE);
	ft_lstdbadd_back(&env->pipex_stack.head, env->pipex_stack.tail);
	env->pipex_stack.total_item++;
	return (EXIT_SUCCESS);
}

static void	print_pipex_stack_int(void *v_content)
{
	int		i;
	t_cell_pipex	*content;

	content = (t_cell_pipex*)v_content;
	i = 0;
	printf("PRINT CELL :\n");
	while (content->args[i])
	{
		printf("%d[%s]\n", i, content->args[i]);
		i++;
	}
}

void	print_pipex_stack(t_env *env)
{
	printf("        Pipex stack, size : %d\n", env->pipex_stack.total_item);
	if (env->pipex_stack.head)
		ft_lstdbiter_fun_first(env->pipex_stack.head,
			&print_pipex_stack_int);
	printf("        End Pipex stack : %d\n", env->pipex_stack.total_item);
}