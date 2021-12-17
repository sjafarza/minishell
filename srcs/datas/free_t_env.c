/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/12/17 09:41:16 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_t_env(t_env *env)
{
	clean_env_vars(env);
	free_array(env->paths);
	if (env->cwd)
		free(env->cwd);
	clear_parsed_groups_stack(env);
	clear_pipex_stack(env);
	*env = (t_env){0};
}
