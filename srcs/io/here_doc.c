/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:04:01 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 14:16:29 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	gnl_next(t_env	*env, char **line, char *s, int outfile_fd)
{
	int		i;
	t_line	line_handle;

	i = 0;
	line_handle.line = line;
	line_handle.i = &i;
	if ((ft_strncmp(*line, s, ft_strlen(s)) == 0)
		&& (ft_strlen(s) == (ft_strlen(*line))))
	{
		free(*line);
		*line = NULL;
		return (EXIT_SUCCESS);
	}
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			parse_dollar_for_double_quotes(&line_handle, NULL,
				(t_parse_utils){env, &i, NULL, NULL});
		i++;
	}
	write(outfile_fd, *line, ft_strlen(*line));
	write(outfile_fd, "\n", 1);
	free(*line);
	*line = NULL;
	return (-EXIT_FAILURE);
}

int	here_doc(t_env *env, t_cell_io *io_cell)
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
		if (gnl_next(env, &line, io_cell->arg, outfile_fd) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		line = readline("> ");
		if (!line)
			return (EXIT_CTRL_D);
	}
	return (EXIT_CTRL_D);
}
