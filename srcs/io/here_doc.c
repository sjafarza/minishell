/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:04:01 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 00:04:04 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_next_line(char **line)
{
	char	*input;
	char	buf;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	input = malloc(sizeof(char) * 9450);
	if (!line || !input)
		return (-1);
	ret = read(0, &buf, 1);
	while (ret > 0 && buf != '\n' && buf != '\0')
	{
		input[i] = buf;
		i++;
		ret = read(0, &buf, 1);
	}
	if (i > 0)
		input[i] = '\n';
	input[++i] = '\0';
	*line = input;
	return (ret);
}

void    gnl_next(char **line, int *fds)
{
        write(fds, *line, ft_strlen(*line));
        free(*line);
}

void    here_doc(t_cell_io *io_cell)
{
        int     infile_fd;
        char    *line;

        infile_fd = open(io_cell->arg, O_RDONLY, 0777);
        if (infile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
        while (get_next_line(&line) == 1)
                        gnl_next(&line, infile_fd);        
	return (dup2(infile_fd, STDIN_FILENO));
}
