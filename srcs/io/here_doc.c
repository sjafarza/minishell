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

/*int     check_fds(t_cell_io *args, char **av, int ac)
{
        if (args->fd_in != 500)
        {
                if (args->fd_in < 0)
                {
                        perror(av[1]);
                }
        }
        if (args->fd_out < 0)
        {
                perror(av[ac - 1]);
                exit(1);
        }
        return (1);
}

int     prep(t_cell_io *args, char **av, int ac, int *fds)
{
        pid_t   pid;

        args->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        args->fd_in = 500;
        check_fds(args, av, ac);
        args->i = 3;
        if (pipe(fds) == -1)
        {
                perror("pipe()");
                return (-2);
        }
        pid = fork();
        if (pid == -1)
        {
                perror("fork()");
                return (-2);
        }
        return (pid);
}
void    gnl_next(char **line, char **av, int *fds)
{
        if (ft_strncmp(*line, av[2], ft_strlen(av[2])) == 0
                && ft_strlen(av[2]) == (ft_strlen(*line) - 1))
        {
                free(*line);
                exit(0);
        }
        write(fds[1], *line, ft_strlen(*line));
        free(*line);
}

void    here_doc(t_cell_io *args, char **av, int ac)
{
        int             fds[2];
        pid_t   pid;
        char    *line;

        pid = prep(args, av, ac, fds);
        if (pid == -2)
                return ;
        else if (pid == 0)
        {
                close(fds[0]);
                while (get_next_line(&line) == 1)
                        gnl_next(&line, av, fds);
        }
        else
        {
                close(fds[1]);
                if (dup2(fds[0], STDIN_FILENO) == -1)
                        exit(1);
                waitpid(pid, NULL, 0);
        }
}*/
