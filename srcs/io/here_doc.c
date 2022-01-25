/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:04:01 by saray             #+#    #+#             */
/*   Updated: 2022/01/25 21:02:39 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	gnl_next(char **line, char *s, int outfile_fd)
{
	if ((ft_strncmp(*line, s, ft_strlen(s)) == 0)
		&& (ft_strlen(s) == (ft_strlen(*line))))
	{
		free(*line);
		*line = NULL;
		return (EXIT_SUCCESS);
	}
	write(outfile_fd, *line, ft_strlen(*line));
	write(outfile_fd, "\n", 1);
	free(*line);
	*line = NULL;
	return (-EXIT_FAILURE);
}

int	here_doc(t_cell_io *io_cell)
{
	char	*line;
	int		outfile_fd;

	outfile_fd = open(TMP_FILE_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	signal(SIGQUIT, ft_sig_ctr_backslash2);
	signal(SIGINT, ft_sig_ctr_c2);
	line = readline("> ");
	while (line)
	{
		if (gnl_next(&line, io_cell->arg, outfile_fd) == EXIT_SUCCESS)
			break ;
		line = readline("> ");
		if (!line)
			return (EXIT_CTRL_D);
	}
	return (-EXIT_FAILURE);
}
