/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdblast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/14 18:40:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list_double	*ft_lstdblast_int(t_list_double *lst)
{
	if (lst->next)
		return (ft_lstdblast_int(lst->next));
	return (lst);
}

t_list_double	*ft_lstdblast(t_list_double *lst)
{
	if (lst)
		return (ft_lstdblast_int(lst));
	return (lst);
}
