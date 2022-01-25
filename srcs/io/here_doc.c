/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:04:01 by saray             #+#    #+#             */
/*   Updated: 2022/01/25 11:24:01 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	gnl_next(char **line, char *s, int fds)
{
	(void)fds;
	if ((ft_strncmp(*line, s, ft_strlen(s)) == 0)
		&& (ft_strlen(s) == (ft_strlen(*line))))
	{
		free(*line);
		return (EXIT_SUCCESS);
	}
	free(*line);
	return (-EXIT_FAILURE);
}

int	here_doc(t_cell_io *io_cell)
{
	char	*line;

	signal(SIGQUIT, ft_sig_ctr_backslash2);
	signal(SIGINT, ft_sig_ctr_c2);
	line = readline("> ");
	while (line)
	{
		if (gnl_next(&line, io_cell->arg, 1) == EXIT_SUCCESS)
			break ;
		line = readline("> ");
	}
	if (!line)
		return (2);
	if (dup2(1, STDIN_FILENO) != -1)
		return (EXIT_SUCCESS);
	return (-EXIT_FAILURE);
}
