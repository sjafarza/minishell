/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_openers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/27 19:43:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_file_and_prep_redirect(t_env *env, char *path)
{
	int				infile_fd;

	infile_fd = open(path, O_RDONLY, 0777);
	if (infile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	env->final_input_fd = infile_fd;
	return (EXIT_SUCCESS);
}

int	open_input_simple(t_env *env, t_cell_io *io_cell)
{
	return (open_file_and_prep_redirect(env, io_cell->arg));
}

#define WARNING_CTR_D	"msh:avertissement :«here-document» à la ligne * "

int	open_input_double(t_env *env, t_cell_io *io_cell)
{
	int	ret;

	ret = here_doc(env, io_cell);
	if (ret == EXIT_CTRL_D)
	{
		write(1, WARNING_CTR_D, ft_strlen(WARNING_CTR_D));
		printf("délimité par fin du fichier(au lieu de « %s »)\n", io_cell->arg);
	}
	return (open_file_and_prep_redirect(env, TMP_FILE_PATH));
}

int	open_output_simple(t_env *env, t_cell_io *io_cell)
{
	int	outfile_fd;

	(void)env;
	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (dup2(outfile_fd, STDOUT_FILENO) == STDOUT_FILENO)
		return (EXIT_SUCCESS);
	return (-EXIT_FAILURE);
}

int	open_output_double(t_env *env, t_cell_io *io_cell)
{
	int	outfile_fd;

	(void)env;
	outfile_fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (dup2(outfile_fd, STDOUT_FILENO) == STDOUT_FILENO)
		return (EXIT_SUCCESS);
	return (-EXIT_FAILURE);
}
