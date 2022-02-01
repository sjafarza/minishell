/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:27:41 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 14:12:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// ctrl+c = SIGINT *  , ctrl+\ = SIGQUIT , ctrl+D = exit

void	ft_sig_ctr_c2(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	write (1, "\033[8D\033[0K", 8);
	g_status = 130;
	exit(1);
}

void	ft_sig_ctr_c(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	g_status = 130;
}

void	ft_sig_ctr_backslash2(int sig)
{
	(void)sig;
	g_status = 0;
}

void	ft_sig_ctr_backslash(int sig)
{
	(void)sig;
	write (1, "\033[2D\033[0K", 8);
	g_status = 0;
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write (1, "\033[2D\033[0K", 8);
		g_status = 131;
	}
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}
