/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:26:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/13 16:15:44 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_link	*ft_search_target(t_link *head, int target)
{
	t_link	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->identifier == OPEN_PAR)
		{
			while (tmp->identifier != CLOSE_PAR)
			{
				tmp = tmp->next;
				if (!tmp)
					return (NULL);
			}
		}
		if (tmp->identifier == target)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	*ft_fill_priority(void)
{
	int	*priority;
	int	i;
	int	j;

	priority = malloc(LEN_ENUM * sizeof(int));
	memset(priority, 0, sizeof(int));
	if (!priority)
		return (NULL);
	i = 0;
	j = 7;
	while (i < LEN_ENUM)
	{
		priority[i] = j;
		i++;
		j--;
	}
	return (priority);
}

t_link	*ft_find_hightest_proirity(t_link *head)
{
	t_link	*target;
	int		*priority;
	int		i;

	i = 0;
	target = NULL;
	priority = ft_fill_priority();
	while (i < LEN_ENUM)
	{
		target = ft_search_target(head, priority[i]);
		if (target)
		{
			printf("target 1 %s\n", target->command);
			return (free(priority), target);
		}
		i++;
	}
	return (free(priority), target);
}
