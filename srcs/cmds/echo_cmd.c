/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:47:48 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/04 09:55:36 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int verification_arg_n(const char	*s)
{
	int	i;

	i = 0;
	if (!s)
		return (-EXIT_FAILURE);
	if (!ft_strncmp(s, "-n", 2))
	{
		if (ft_strlen(s) == 2)
			return (EXIT_SUCCESS);
		while (++i < (int)ft_strlen(s))
		{
			if (s[i] != 'n'/* || (s[i] != '\\')*/)
				return (-EXIT_FAILURE);
			/*if (s[i] == '\\' && (s[i + 1] == '\\' || s[i - 1] == '\\'))
				return (-EXIT_FAILURE);*/
		}
	return (EXIT_SUCCESS);	
	}
	/*if (!ft_strncmp(s, "\\-n", 3) || !ft_strncmp(s, "-\n", 3))
	{
		if (ft_strlen(s) == 3)
			return (EXIT_SUCCESS);
			while (++i < (int)ft_strlen(s))
		{
			if (s[i] != 'n' || (s[i] != '\\'))
				return (-EXIT_FAILURE);
			if (s[i] == '\\' && (s[i + 1] == '\\' || s[i - 1] == '\\'))
				return (-EXIT_FAILURE);
		}
	}*/
		//printf("Yest\n");		
		return (-EXIT_FAILURE);
}

int	echo_cmd(t_env *env, const char *cmd, const char **args)
{
	int		i;

	(void)cmd;
	(void)env;
	i = 1;
	//echo \-n hey && -\n hey 
	// echo -nnnnnnnn hi
	// echo  -n\nnnnn  hi    or  echo  \-nnnn hi
	
	/*if (args[1] && ((!ft_strncmp(args[1], "-n", 2) && ft_strlen(args[1]) == 2) || \
			((!ft_strncmp(args[1], "-\n", 3) || (!ft_strncmp(args[1], "\\-n", 3))) \
				 && ft_strlen(args[1]) == 3)))*/
	if (verification_arg_n(args[1]) == EXIT_SUCCESS)			 
	{
		i++;
		while (args[i] && !ft_strncmp(args[i], "-n", 2) \
			&& ft_strlen(args[i]) == 2)
			i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	//if (args[1] && !ft_strncmp(args[1], "-n", 2) && ft_strlen(args[1]) == 2)
	/*if (args[1] && ((!ft_strncmp(args[1], "-n", 2) && ft_strlen(args[1]) == 2) || \
			((!ft_strncmp(args[1], "-\n", 3) || (!ft_strncmp(args[1], "\\-n", 3))) \
				 && ft_strlen(args[1]) == 3)))*/
	if (verification_arg_n(args[1]) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	printf("\n");
	return (EXIT_SUCCESS);
}
