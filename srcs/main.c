/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2021/11/28 17:05:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	main(int ac, char **av, char **env_bash)
{
	int		i;
	char	*line;
	t_env	env;

	(void)ac;
	(void)av;
	i = -1;
	line = NULL;
	env = (t_env){0};

	//1- recover vaiable env & all of path in PATH
	printf("1- recovr variable env et PATH by 2 function a_env & a_path\n\n");
	// a_env = ft_recover_env(env);

	if (init_env_vars(&env, env_bash) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED\n");
	if (init_path(&env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH PATH\n");
	// a_path = ft_path(env_bash);
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
	// 2-scan the teminal
	g_test_line = readline("mshell$ ");
	while (g_test_line)
	{
		// printf("line = %s\n", line);
		// printf("2- Bilding list of Token in function ft_lexer\n\n");
		// if (!ft_line_is_vide(line))
		// 	add_history(line);
		printf("LINE BEFORE [%s]\n", g_test_line);
		replace_in_str(&env, &g_test_line);
		printf("LINE AFTER [%s]\n", g_test_line);
		// if (ft_find_error(line) && ft_lexer(line))
		// {
		// 	printf("3- lexer control error \n");
		// 	printf("4- parse \n");
		// 	printf("5- Build AST \n");
		// 	printf("6- execut \n");
		// }
		free(g_test_line);
		g_test_line = readline("mshell$ ");
	}
	free(g_test_line);
	// ft_free(a_env, a_path);

	free_t_env(&env);
	return (1);
}
