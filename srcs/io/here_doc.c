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

static int	get_next_line(char **line, int	**chek)
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
	if (ret == 0)
		**chek = 1;
	return (ret);
}

static int    gnl_next(char **line,char *s, int fds)
{
	(void)fds;
	if ((ft_strncmp(*line, s, ft_strlen(s)) == 0)
		&& (ft_strlen(s) == (ft_strlen(*line) - 1)))
	{
		free(*line);
		return(EXIT_SUCCESS);
	}
        free(*line);
		return (-EXIT_FAILURE);
}

int    here_doc(t_cell_io *io_cell, int *chek)
{
	char    *line;
	
	signal(SIGQUIT, ft_sig_ctr_backslash2);
	signal(SIGINT, ft_sig_ctr_c);
	write(1,"> ", 2);
    while (get_next_line(&line, &chek) == 1)
	{
		write(1,"> ", 2);
		if(gnl_next(&line, io_cell->arg, 1) == EXIT_SUCCESS)
			break ;
	}
	if (dup2(1, STDIN_FILENO) != -1)
                return (EXIT_SUCCESS);
        return (-EXIT_FAILURE);        
}
