/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_lstadd_back_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:05:30 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/25 10:35:44 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_dbl_lstadd_back(t_link **lst, t_link *new)
{
	t_link	*last;

	if (NULL == lst)
		return ;
	if (NULL == *lst)
	{
		*lst = new;
		return ;
	}
	last = ft_dbl_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

t_link	*ft_dbl_lstadd_front(t_link **lst, t_link *new)
{
	if (NULL == lst)
		return (NULL);
	if (NULL == *lst)
		return (new);
	new->next = *lst;
	return (new);
}
