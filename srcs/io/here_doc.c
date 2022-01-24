/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:04:01 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:30:30 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_next_line(char **line)
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

static int    gnl_next(char **line,char *s, int fds)
{
	if (ft_strncmp(*line, s, ft_strlen(s) == 0
		&& ft_strlen(s) == (ft_strlen(*line) - 1)))
	{
		free(*line);
		return(EXIT_SUCCESS);
	}
        write(fds, *line, ft_strlen(*line));
        free(*line);
		return (-EXIT_FAILURE);
}

int    here_doc(t_cell_io *io_cell)
{
        //int     infile_fd;
        char    *line;

        /*infile_fd = open(io_cell->arg, O_RDONLY, 0777);
        if (infile_fd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);*/
        while (get_next_line(&line) == 1)
                        if (gnl_next(&line, io_cell->arg, 1) == EXIT_SUCCESS)
							break ;
	if (dup2(1, STDIN_FILENO) != -1)
                return (EXIT_SUCCESS);
        return (-EXIT_FAILURE);        
}
