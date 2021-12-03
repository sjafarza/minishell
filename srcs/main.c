/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2021/12/02 17:44:13 by scarboni         ###   ########.fr       */
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

	if (init_env_vars(&env, env_bash) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED\n");
	if (init_path(&env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH PATH\n");
	if (init_cwd(&env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH CWD\n");
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
	// 2-scan the teminal
	line = readline("mshell$ ");
	while (line)
	{
		// printf("line = %s\n", line);
		// printf("2- Bilding list of Token in function ft_lexer\n\n");
		// if (!ft_line_is_vide(line))
		if (line && ft_isprint(line[0]) && !ft_is_blank(line[0]))
			add_history(line);
		char *line_to_edit = ft_strdup(line);
		char **arg = NULL;
		int i = 0;
		printf("RESULT %d\n", extract_args(&line_to_edit, &arg));
		if (arg)
		{
			while (arg[i])
			{
				printf("PARSED ARG :%s\n", arg[i]);
				i++;
			}
			free_array(arg);
		}
		free(line_to_edit);
		// printf("LINE BEFORE [%s]\n", line);
		// replace_in_str(&env, &line);
		// printf("LINE AFTER [%s]\n", line);

		// if (ft_find_error(line) && ft_lexer(line))
		// {
		// 	printf("3- lexer control error \n");
		// 	printf("4- parse \n");
		// 	printf("5- Build AST \n");
		// 	printf("6- execut \n");
		// }
		free(line);
		line = readline("mshell$ ");
	}
	free(line);
	rl_clear_history();
	free_t_env(&env);
	return (1);
}
