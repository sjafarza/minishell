/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:03:13 by saray             #+#    #+#             */
/*   Updated: 2021/11/29 18:21:22 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env_bash)
{
	int		i;
	char	*line;
	char	**word;
	t_env	env;

	(void)ac;
	(void)av;
	i = -1;
	line = NULL;
	word = NULL;
	env = (t_env){0};

	//1- recover vaiable env & all of path in PATH
	
	if (init_env_vars(&env, env_bash) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED\n");
	if (init_path(&env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH PATH\n");
	if (init_cwd(&env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH CWD\n");
	//2- signal
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
	//3-scan the teminal
	line = readline("mshell$ ");
	while (line)
	{
		if (line && ft_isprint(line[0]) && !ft_is_blank(line[0]))
			add_history(line);
		printf("LINE BEFORE [%s]\n", line);
		replace_in_str(&env, &line);
		printf("LINE AFTER [%s]\n", line);
		word = ft_split(line , ' ');
		select_right_cmd(&env, word[0], (const char**) word);
		char *line_to_edit = ft_strdup(line);
		printf("RESULT %d\n", extract_parsed_groups(&env, &line_to_edit));
		print_parsed_group_stack(&env);
		clear_parsed_groups_stack(&env);
		free(line_to_edit);
		free(line);
		line = readline("mshell$ ");
	}
	printf("exit\n");
	if (line)
		free(line);
	rl_clear_history();
	free_t_env(&env);
	return (1);
}
