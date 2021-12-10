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

}


