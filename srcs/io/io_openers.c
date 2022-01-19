/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_openers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/19 15:42:20 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



int		open_input_simple(t_list_double *pipex_node, t_cell_io *io_cell)
{
	int				infile_fd;

	(void)pipex_node;
	infile_fd = open(io_cell->arg, O_RDONLY, 0777);
	if (infile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(infile_fd, STDIN_FILENO));
}

int		open_input_double(t_list_double *pipex_node, t_cell_io *io_cell)
{
	(void)pipex_node;
	(void)io_cell;
	//GNL? Other ?
	return (EXIT_SUCCESS);
}

int		open_output_simple(t_list_double *pipex_node, t_cell_io *io_cell)
{
	int	outfile_fd;

	(void)pipex_node;
	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(outfile_fd, STDOUT_FILENO));
}

int		open_output_double(t_list_double *pipex_node, t_cell_io *io_cell)
{
	int	outfile_fd;

	(void)pipex_node;
	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(outfile_fd, STDOUT_FILENO));
}
