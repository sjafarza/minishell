/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdb_get_elem_by_nb_from_back.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:03:36 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list_double	*ft_lstdb_get_elem_by_nb_from_back_int(
t_list_double *lst, int nb)
{
	if (!lst || nb < 0)
		return (NULL);
	else if (nb == 0)
		return (lst);
	return (ft_lstdb_get_elem_by_nb_from_back_int(lst->prev, nb - 1));
}

t_list_double	*ft_lstdb_get_elem_by_nb_from_back(t_list_double *lst, int nb)
{
	if (!lst || nb < 0)
		return (NULL);
	return (ft_lstdb_get_elem_by_nb_from_back_int(lst, nb));
}
