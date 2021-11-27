/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbcount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 11:55:53 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

#define TARGET 0
#define NOT_TARGET -1
#define ERROR -2

static int	ft_lstdbcount_int(t_list_double *lst, void *target_util,
int (*is_target)(void*, void*))
{
	int	tmp;

	if (!lst)
		return (NOT_TARGET);
	tmp = ft_lstdbcount_int(lst->next, target_util, is_target);
	if (is_target(target_util, lst->content) == TARGET)
		return (tmp + 1);
	return (tmp);
}

int	ft_lstdbcount(t_list_double *head_src, void *target_util,
int (*is_target)(void*, void*))
{
	int	tmp;

	if (!head_src || !is_target)
		return (ERROR);
	tmp = ft_lstdbcount_int(head_src, target_util, is_target);
	if (tmp == NOT_TARGET)
		return (0);
	return (tmp + 1);
}
