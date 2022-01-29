/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_openers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/29 15:44:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_close_and_replace(int **dst_fd, int *src_fd)
{
	if (*dst_fd)
	{
		if (**dst_fd >= 0)
			close(**dst_fd);
		**dst_fd = -1;
	}
	*dst_fd = src_fd;
}

int	open_file_and_prep_redirect(t_env *env, char *path, int *fd)
{
	*fd = open(path, O_RDONLY, 0777);
	if (*fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	ft_close_and_replace(&env->final_input_fd, fd);
	return (EXIT_SUCCESS);
}

int	open_input_simple(t_env *env, t_cell_io *io_cell)
{
	return (open_file_and_prep_redirect(env, io_cell->arg, &(io_cell->fd)));
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
	return (open_file_and_prep_redirect(env, TMP_FILE_PATH, &(io_cell->fd)));
}

int	open_output_simple(t_env *env, t_cell_io *io_cell)
{
	(void)env;
	io_cell->fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (io_cell->fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	ft_close_and_replace(&env->final_output_fd, &(io_cell->fd));
	return (EXIT_SUCCESS);
	// if (dup2(io_cell->fd, STDOUT_FILENO) == STDOUT_FILENO)
	// 	return (EXIT_SUCCESS);
	// return (-EXIT_FAILURE);
}

int	open_output_double(t_env *env, t_cell_io *io_cell)
{
	(void)env;
	io_cell->fd = open(io_cell->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (io_cell->fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	ft_close_and_replace(&env->final_output_fd, &(io_cell->fd));
	return (EXIT_SUCCESS);
}
