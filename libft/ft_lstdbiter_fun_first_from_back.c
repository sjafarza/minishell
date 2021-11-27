/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbiter_fun_first_from_back.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/14 18:36:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdbiter_fun_first_from_back(t_list_double *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	(*f)(lst->content);
	ft_lstdbiter_fun_first_from_back(lst->prev, f);
}
