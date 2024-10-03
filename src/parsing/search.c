/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:26:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/10/03 10:23:25 by oouaadic         ###   ########.fr       */
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
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		while (tmp && tmp->identifier == CLOSE_PAR)
		{
			while (tmp && tmp->identifier != OPEN_PAR && key == 0)
			{
				if (tmp->identifier == CLOSE_PAR)
					key++;
				else if (tmp->identifier == OPEN_PAR)
					key--;
				tmp = tmp->prev;
			}
		}
		if (tmp->identifier == target[0] || tmp->identifier == target[1])
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
