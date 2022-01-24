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
	int	chek;
	int	ret;

	(void)io_cell;
	chek = 0;
	//GNL? Other ?
	ret = here_doc(io_cell, &chek);
	if (chek == 1 && ret != EXIT_SUCCESS)
		{
			printf("msh: avertissement : « here-document » à la ligne * délimité par la fin du fichier (au lieu de « * »)\n");
			chek = 0;
			exit(1) ;
		}

	return (ret);
	//return (EXIT_SUCCESS);
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
