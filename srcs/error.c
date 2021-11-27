/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 21:44:56 by scarboni         ###   ########.fr       */
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

int   ft_find_quotes(char *line)
{       
        int     i;
        int     q;
        int     dq;

        i = -1;
        q = 0;
        dq = 0;
        while (line[++i])
        {
                if (line[i] == '\'')
                        ++q;
                if (line[i] == '\"')
                        ++dq;
                
        }
	if (q == 0 && dq == 0)
		return (0);
	return (1);
}
int   ft_quotes_is_paire(char *line)
{       
        int     i;
        int     q;
        int     dq;

        i = -1;
        q = 0;
        dq = 0;
        while (line[++i])
        {
                if (line[i] == '\'')
                        ++q;
                if (line[i] == '\"')
                        ++dq;
                
        }
	if (q % 2 || dq % 2)
	{
		printf ("msh : Not interpret unclosed quotes \n");
		return (1);
	}
	return (0);
}

int	ft_line_is_vide(char	*s)
{
	int		i;
	size_t	v;

	i = -1;
	v = 0;
	while (s[++i])
		if(ft_is_blank(s[i]))
                        v++;
	if (v == ft_strlen(s))
		return (1);
	return (0);
}


int	ft_find_error(char *line)
{
	int	i;

	//ft_del_emptyspace(line);
	if (ft_line_is_vide(line))
		return (0);
	i = 0;
	if (ft_quotes_is_paire(line))
		return (0);
        //1-3 syntax of comand
	/*if (!ft_is_cmd(line))
	{
		printf ("msh : command not found : %s\n", line);
		ft_free_line(line);
		return (1);
	}*/
	return (1);
}
			
