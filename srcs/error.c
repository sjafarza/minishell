/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 13:02:22 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_free_line(char	**s)
{
	int i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	ft_is_cmd(char *s)
{
	int	l;

	//is correct cmd return 1, in error retun 0
	l = ft_strlen(s);
	if(!ft_memcmp(s, "echo", 4) && l == 4)
		return (1);
	if(!ft_memcmp(s, "cd", 2) && l == 2)
		return (1);
	if(!ft_memcmp(s, "pwd", 3) && l == 3)
		return (1);
	if(!ft_memcmp(s, "export", 6) && l == 6)
		return (1);
	if(!ft_memcmp(s, "unset", 6) && l == 6)
		return (1);
	if(!ft_memcmp(s, "env", 3) && l == 3)
		return (1);
	if(!ft_memcmp(s, "exit", 5) && l == 5)
		return (1);
	return (0);
}


int	ft_find_error(char **line)
{
	int	i;

	ft_del_emptyspace(line);
	i = 0;
	if (!ft_is_cmd(line[0]))
	{
		printf ("msh : command not found : %s\n", line[i]);
		ft_free_line(line);
		return (1);
	}
	return (0);
}
			
