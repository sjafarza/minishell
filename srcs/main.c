/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 16:43:06 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init(int ac, char **av, t_env *env, char **env_bash)
{
	(void)ac;
	(void)av;
	g_status = 0;
	*env = (t_env){0};
	if (init_env_vars(env, env_bash) != EXIT_SUCCESS)
	{
		printf("AN ERROR OCCURED\n");
		free_t_env(env);
		exit(1);
	}
	if (init_path(env) != EXIT_SUCCESS)
	{
		printf("AN ERROR OCCURED WITH PATH\n");
		free_t_env(env);
		exit(1);
	}
	if (init_cwd(env) != EXIT_SUCCESS)
	{
		printf("AN ERROR OCCURED WITH CWD\n");
		free_t_env(env);
		exit(1);
	}
}

void	loop(t_env *env, char *line)
{
	if (line && ft_isprint(line[0]) && !ft_is_blank(line[0]))
		add_history(line);
	if (!(extract_parsed_groups(env, &line) == EXIT_SUCCESS))
		printf("Error in parsing\n");
	else
	{
		if (!(execute_parsed_groups_stack(env) == EXIT_SUCCESS))
			printf("Error in parsing\n");
		else
		{
			if (!(execute_pipex_stack(env) == EXIT_SUCCESS))
				printf("Error in execution\n");
		}
	}
	free(line);
	line = NULL;
	clear_parsed_groups_stack(env);
	clear_pipex_stack(env);
}

int	main(int ac, char **av, char **env_bash)
{
	char	*line;
	t_env	env;

	line = NULL;
	init(ac, av, &env, env_bash);
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
	line = readline("mshell$ ");
	while (line)
	{
		loop(&env, line);
		if (env.exit_value == EXIT_MINISHELL)
			break ;
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_ctr_backslash);
		line = readline("mshell$ ");
	}
	printf("exit\n");
	if (line)
		free(line);
	free_t_env(&env);
	return (0);
}
