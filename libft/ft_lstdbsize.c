/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/19 16:54:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstdbsize_int(int current, t_list_double *lst)
{
	if (lst)
		return (ft_lstdbsize_int(current + 1, lst->next));
	return (current);
}

int	ft_lstdbsize(t_list_double *lst)
{
	if (lst)
		return (ft_lstdbsize_int(1, lst->next));
	return (0);
}
