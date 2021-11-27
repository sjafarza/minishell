/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/11 14:38:03 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstsize_int(int current, t_list *lst)
{
	if (lst)
		return (ft_lstsize_int(current + 1, lst->next));
	return (current);
}

int	ft_lstsize(t_list *lst)
{
	if (lst)
		return (ft_lstsize_int(1, lst->next));
	return (0);
}
