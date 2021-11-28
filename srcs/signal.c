/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:27:41 by saray             #+#    #+#             */
/*   Updated: 2021/11/28 17:31:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

// ctrl+c = SIGINT  , ctrl+\ = SIGQUIT , ctrl+D = exit

static void	ft_process(int sign_num)
{

	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			//ft_putstr_fd("Quit: 3\n", 1);
			write (1, "Quit: 3\n", 8);
		//	g_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			//ft_putchar_fd('\n', 1);
			write (1, "\n", 1);
		//	g_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
	//	ft_putchar_fd('\n', 1);
		write(1, "\n", 1);
	//	g_status = 1;
	//	prompt();
		write(1, "mshell$ ", 8);
	}
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGQUIT)
		write (1, "\033[2D\033[0K", 8);
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
	}

	if ((sig == SIGINT || sig == SIGQUIT) && g_pid != 0)
		ft_process(sig);
/*	else
	{
		if (sig == SIGINT) // ctrl + c 
		{
			write (1, "\n", 1);
			return ;
			//g_status = 1;
			//write (1, "mshell$ ", 8); ; // prompt();
		 }
		else if (sig ==  SIGQUIT) // ctrl + D
			write (1, "\b\b \b\b", 5);
	} */
}


