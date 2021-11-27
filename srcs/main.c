/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 21:47:29 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// char	**ft_recover_env(char	**env)
// {
// 	int	i;
// 	char	**a_env;

// 	i = -1;
// 	while (env[++i]);
// 	a_env = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!a_env)
// 		return (NULL);
// 	i = -1;
// 	while (env[++i])
// 		a_env[i] = ft_strdup(env[i]);
// 	a_env[i] = NULL;
// 	/*i = -1;
// 	while (a_env[++i])
// 		printf("a_env[%d]= %s\n", i, a_env[i]);*/
// 	return (a_env);
// }

#define PATH_STR "PATH="
#define PATH_LEN 5

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
		if (!ft_memcmp(a_env[i], PATH_STR, PATH_LEN))
		{
			tmp = ft_substr(a_env[i], PATH_LEN, ft_strlen(a_env[i]) - PATH_LEN);
			break ;
		}
	}
	if (tmp)
	{
		a_path = ft_split(tmp, ':');
		free(tmp);
	}
/*	i = -1;
	while (a_path[++i])
		printf("**a_path[%d] = %s\n", i, a_path[i]);*/
	return (a_path);
}

int	main(int ac, char **av, char **env_bash)
{
	int	i;
	// char	**a_env;
	char	**a_path;
	char	*line;
	t_env	env;

	i = -1;
	(void)ac;
	(void)av;
	line = NULL;

	//1- recover vaiable env & all of path in PATH
	printf("1- recovr variable env et PATH by 2 function a_env & a_path\n\n");
	// a_env = ft_recover_env(env);

	if(init_env_vars(&env, env_bash) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED\n");
	init_path(&env);
	a_path = ft_path(env_bash);
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
	
	// 2-scan the teminal
	line = readline("mshell$ ");
	while (line)
	{
		printf("line = %s\n", line);
		printf("2- Bilding list of Token in function ft_lexer\n\n");
		if (!ft_line_is_vide(line))
			add_history(line);
		printf("LINE BEFORE [%s]\n", line);
		replace_in_str(&env, &line);
		printf("LINE AFTER [%s]\n", line);
		if (ft_find_error(line) && ft_lexer(line))
		{
			printf("3- lexer control error \n");
			printf("4- parse \n");
			printf("5- Build AST \n");
			printf("6- execut \n");
		}
		free(line);
		line = readline("mshell$ ");
	}
	free(line);
	// ft_free(a_env, a_path);
	return (1);
}
