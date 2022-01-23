/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_openers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/23 22:15:03 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



int		open_input_simple(t_cell_io *io_cell)
{
	int				infile_fd;

	infile_fd = open(io_cell->arg, O_RDONLY, 0777);
	if (infile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(infile_fd, STDIN_FILENO));
}

int		open_input_double(t_cell_io *io_cell)
{
	(void)io_cell;
	//GNL? Other ?
	// 1) Est_ce que io_cell == "here_doc" in cat<<here_doc?  , (here_doc peut etre n'import mots)
	// 2) j'ai besion env pour avoir fonctioner "here_doc"
	//if (ft_strncmp(io_cell->arg, "here_doc", 8) == 0/* 3) && "ac" >= 6*/) /* 3-1) N of arg = 6 for cat<<s*/
	//	here_doc(&(io_cell), io_cell->arg, ac);
	return (EXIT_SUCCESS);
}

int		open_output_simple(t_cell_io *io_cell)
{
	int	outfile_fd;

	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(outfile_fd, STDOUT_FILENO));
}

int		open_output_double(t_cell_io *io_cell)
{
	int	outfile_fd;

	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (dup2(outfile_fd, STDOUT_FILENO));
}
