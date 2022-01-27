/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipex_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/27 14:39:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_pipex_stack_int(void *v_content)
{
	int				i;
	t_cell_pipex	*content;

	content = (t_cell_pipex *)v_content;
	i = 0;
	printf("PRINT CELL :\n");
	while (content->args[i])
	{
		printf("%d[%s]\n", i, content->args[i]);
		i++;
	}
	print_io_stack(&content->io_stack);
}

void	print_pipex_stack(t_env *env)
{
	printf("        Pipex stack, size : %d\n", env->pipex_stack.total_item);
	if (env->pipex_stack.head)
		ft_lstdbiter_fun_first(env->pipex_stack.head,
			&print_pipex_stack_int);
	printf("        End Pipex stack : %d\n", env->pipex_stack.total_item);
}
