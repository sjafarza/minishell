/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 20:58:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_cmd_error(const char *cmd_name, const char *e1, const char *e2,
	const char *e3)
{
	ft_putstr_fd(PROMPT_STR, STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (e1)
		ft_putstr_fd((char *)e1, STDERR_FILENO);
	if (e2)
		ft_putstr_fd((char *)e2, STDERR_FILENO);
	if (e3)
		ft_putstr_fd((char *)e3, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
