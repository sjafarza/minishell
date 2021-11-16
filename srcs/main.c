/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2021/11/15 10:48:01 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

char	**ft_recover_env(char	**env)
{
	int	i;
	char	**a_env;

	i = -1;
	while (env[++i]);
	a_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!a_env)
		return (NULL);
	i = -1;
	while (env[++i])
		a_env[i] = ft_strdup(env[i]);
	a_env[i] = NULL;
	/*i = -1;
	while (a_env[++i])
		printf("a_env[%d]= %s\n", i, a_env[i]);*/
	return (a_env);
}

char	**ft_path(char	**a_env)
{
	int	i;
	char	*tmp;
	char	**a_path;

	i = -1;
	a_path = NULL;
	tmp = NULL;
	while (a_env[++i])
	{
		if (!ft_memcmp(a_env[i], "PATH", 4))
		{
			tmp = ft_substr(a_env[i], 4, ft_strlen(a_env[i]) - 4);
			break ;
		}
	}
	if (tmp)
	{
		a_path = ft_split(tmp, ':');
		free(tmp);
	}
	i = -1;
/*	while (a_path[++i])
		printf("**a_path[%d] = %s\n", i, a_path[i]);*/
	return (a_path);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	char	**a_env;
	char	**a_path;
	char	*line;

	i = -1;
	printf("ac = %d, av[%d] = %s\n", ac, ac - 1, av[ac-1]);
	//1- recover vaiable env & all of path in PATH
	a_env = ft_recover_env(env);
	a_path = ft_path(a_env);
	write(1, "mshell$ ",8);
	while (gnl(0, &line) >= 0)
	{
		printf("line = %s\n", line);
		ft_lexer(line);
		printf("1- lexer control error \n");
		printf("2- parse \n");
		printf("3- Build AST \n");
		printf("4- execut \n");
		write(1, "mshell$ ", 8);
	}
	ft_free(a_env, a_path);
	return (1);
}
