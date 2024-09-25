/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:26:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/25 10:51:07 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_link	*ft_search_target(t_link *head, int target[2])
{
	t_link	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (tmp->identifier == OPEN_PAR)
		{
			if (target[1] == OPEN_PAR)
				return (tmp);
			while (tmp->identifier != CLOSE_PAR)
			{
				tmp = tmp->next;
				if (!tmp)
					return (NULL);
			}
		}
		if (tmp->identifier == target[0] || tmp->identifier == target[1])
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_link	*ft_search_target_rev(t_link *head, int target[2])
{
	t_link	*tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->identifier == OPEN_PAR)
		{
			if (target[1] == OPEN_PAR)
				return (tmp);
			while (tmp->identifier != CLOSE_PAR)
			{
				tmp = tmp->prev;
				if (!tmp)
					return (NULL);
			}
		}
		if (tmp->identifier == target[0] || tmp->identifier == target[1])
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
