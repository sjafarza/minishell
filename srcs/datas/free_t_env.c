/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/20 17:51:39 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_t_env(t_env *env)
{
	rl_clear_history();
	clean_env_vars(env);
	free_array(env->paths);
	if (env->cwd)
		free(env->cwd);
	clear_parsed_groups_stack(env);
	clear_pipex_stack(env);
	*env = (t_env){0};
}
