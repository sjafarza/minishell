/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 00:37:55 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_first_eq(char	*s)
{
	int	i;

	if(!s)
		return(-EXIT_FAILURE);
	i = -1;
	while (s[++i])
		if(s[i] == '=')
			return (++i);
	return (0);
}

char	*make_value(char *value)
{
	int	s;
	int n_digit;
	int	i;

	s = 0;
	i = -1;
	if(value[0] == '-')
		return("0");
	printf("befor loop in make_value\n");
	while (value[++i] == '0')
		s++;
	if (s == 0)
		i = 0;
	while ( value[i++] == '+')
	{
		if(ft_strlen(value) > 3)
			return("0");
		s++;	
	}	
	printf("ater loop in make_value s = %d\n", s);
	i = s;
	n_digit = 0;
	while (value[i] && ft_isdigit(value[i]))
	{
		i++;
		n_digit++;
	}
	if (n_digit != ((int)ft_strlen(value) - s) && i != 0)
		return("0");
	if (n_digit == 0)
		return("0");	
	if(n_digit == ((int)ft_strlen(value) - s) && i > 3 && n_digit > 3)	
		return ("1");
	printf("n_digi = %d\n", n_digit);
	printf("i = %d\n", i);	
	if (n_digit == ((int)ft_strlen(value) - s) /*&& i <= 3 */&& n_digit <= 3)
	{
		value = ft_itoa(ft_atoi(value) - 1);
		/*printf("s=%d\n", s);
		printf("i=%d\n", i);
		printf("cccccccekkkkk = value in make = %s\n", value);
		printf("len of value =%zu\n", ft_strlen(value));*/
	}
	return (value);
}

int	ft_add(t_env *env, char	*var) 
{
	char	*value;
	char 	*name;
	t_env_var	*tmp_env_vars;
	int			tmp_env_vars_max;
	int		m;

	name = ft_substr(var, 0, find_first_eq(var) - 1);
	if (name == NULL)
		return(-EXIT_FAILURE);		
	value = ft_substr(var, find_first_eq(var), ft_strlen(var) - find_first_eq(var));
	if (value == NULL)
		value = "";	
	if (ft_strlen(name) == 5 && (ft_strncmp(name, "SHLVL",5) == 0))	
		value = make_value(value);

	printf("2 cccccccekkkkk = value in make = %s\n", value);	
	printf("value =  %s\n", value);
	printf("name =  %s\n", name);
	tmp_env_vars_max = env->env_vars_max + 1;
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);	
	m = tmp_env_vars_max - 1;
	if (fill_tmp(env, tmp_env_vars, name, tmp_env_vars_max) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	/*printf("**************************\n\n");
	int k=0;
	printf("m = Max = %d\n", m);
	while (k <= m)	
	{
		printf("&&&&&tmp_env_vars[%d].value = %s\n", k ,tmp_env_vars[k].value.str);
		k++;

	}
	printf("**************************\n\n");*/
	printf("m , indix for adding in tm, in ft_add = %d\n", m);	
	if (init_str(&tmp_env_vars[m].name, name) != EXIT_SUCCESS \
			|| init_str(&tmp_env_vars[m].value, value) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	if ((ft_strlen(name) == 4) && (ft_strncmp(name, "PATH",4) == 0))
	{
		printf("il faudra qu'on mette a jour env->paths\n");
		//free(env->PATH);
		//env->PATH = fft_strdup(tmp[1]);
	}
	free(env->env_vars);
	env->env_vars = tmp_env_vars;
	env->env_vars_max += 1;
	//free(value);
	//free(name);
	return (EXIT_SUCCESS);	
}

int	add_env_var(t_env *env, char *var)
{
	printf("not find in list \n");
	printf("var = %s\n",var);
	ft_add(env, var);
	return (EXIT_SUCCESS);
}
