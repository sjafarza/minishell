/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:37:32 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 13:45:49 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	ft_free(char	**a_env, char	**a_path)
{
	int	i;

	if (a_env)
	{
		i= -1;
		while (a_env[++i])
			free(a_env[i]);
	free(a_env);
	}
	if (a_path)
	{
		i= -1;
		while (a_path[++i])
			free(a_path[i]);
	free(a_path);
	}
	printf("ft_free is done\n");
}
