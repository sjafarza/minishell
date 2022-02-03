/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2022/02/03 10:03:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init(int ac, char **av, t_env *env, char **env_bash)
{
	(void)ac;
	(void)av;
	*env = (t_env){0};
	printf("THE FUCK bef %p\n", (void *)g_status);
	g_status = &env->exit_value;
	printf("THE FUCK aft %p\n", (void *)g_status);
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
	int	ret;

	if (line)
		add_history(line);
	ret = extract_parsed_groups(env, &line);
	if (!(ret == EXIT_SUCCESS))
		printf("Error in parsing %d\n", ret);
	if (env->parsed_groups_stack.total_item > 0)
	{
		ret = execute_parsed_groups_stack(env);
		if (!(ret == EXIT_SUCCESS))
			printf("Error in parsing %d\n", ret);
		else
		{
			ret = execute_pipex_stack(env);
			if (!(ret == EXIT_SUCCESS))
				printf("Error in execution %d\n", ret);
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
		{
			free_t_env(&env);
			return (env.exit_cmd_value);
		}
		signal(SIGINT, ft_sig_handler);
		signal(SIGQUIT, ft_sig_ctr_backslash);
		line = readline("mshell$ ");
	}
	printf("exit\n");
	free_t_env(&env);
	return (env.exit_cmd_value);
}

void	ft_sig_ctr_c2(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	write (1, "\033[8D\033[0K", 8);
	*g_status = 130;
	exit(1);
}


void	ft_sig_ctr_c(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	*g_status = 130;
}

void	ft_sig_ctr_backslash2(int sig)
{
	(void)sig;
	*g_status = 0;
}

void	ft_sig_ctr_backslash(int sig)
{
	(void)sig;
	write (1, "\033[2D\033[0K", 8);
	*g_status = 0;
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write (1, "\033[2D\033[0K", 8);
	}
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		*g_status = 130;
	}
}
