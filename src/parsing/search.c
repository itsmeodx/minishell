/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:26:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/27 17:56:30 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_link	*ft_search_target(t_link *head, int target[2])
{
	t_link	*tmp;
	int		key;

	key = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->identifier == OPEN_PAR)
		{
			if (target[1] == OPEN_PAR)
				return (tmp);
			while (tmp)
			{
				(tmp->identifier == OPEN_PAR) && (key++);
				if (tmp->identifier == CLOSE_PAR && key-- == 0)
					break ;
				tmp = tmp->next;
			}
		}
		if (!tmp || tmp->identifier == target[0]
			|| tmp->identifier == target[1])
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_link	*ft_search_target_rev(t_link *head, int target[2])
{
	t_link	*tmp;
	int		key;

	key = 0;
	tmp = ft_dbl_lstlast(head);
	while (tmp)
	{
		if (tmp->identifier == CLOSE_PAR)
		{
			while (tmp)
			{
				(tmp->identifier == CLOSE_PAR) && (key++);
				if (tmp->identifier == OPEN_PAR)
					if (key-- == 0)
						break ;
				tmp = tmp->prev;
			}
		}
		if (!tmp)
			return (NULL);
		if ((tmp->identifier == target[0] || tmp->identifier == target[1]))
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
