/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:27:41 by saray             #+#    #+#             */
/*   Updated: 2021/12/04 09:16:09 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// ctrl+c = SIGINT  , ctrl+\ = SIGQUIT , ctrl+D = exit

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
		//printf("ok\n");
		write (1, "\033[2D\033[0K", 8);
		g_status = 0;
	}
	if (sig == SIGINT )
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}


