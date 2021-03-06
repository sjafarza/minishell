/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:27:41 by saray             #+#    #+#             */
/*   Updated: 2022/02/03 10:37:20 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// ctrl+c = SIGINT *  , ctrl+\ = SIGQUIT , ctrl+D = exit

void	init_global(t_env *env)
{
	g_status = &env->exit_value;
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
