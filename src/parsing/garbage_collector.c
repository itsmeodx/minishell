/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:41:42 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/08 15:08:01 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_garbage_add_back(t_garbage **garbage, t_garbage *new)
{
	t_garbage	*tmp;

	if (!*garbage)
	{
		*garbage = new;
		return ;
	}
	tmp = *garbage;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_garbage_new(ptr);
	return (ptr);
}

void	ft_garbage_new(t_link *ptr)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = NULL;
	ft_garbage_add_back(&g_data.garbage, new);
}

void	ft_garbage_clear(t_garbage **lst)
{
	t_garbage	*twp;
	t_garbage	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		twp = current;
		current = current->next;
		if (twp->ptr)
		{
			free(twp->ptr->command);
			free(twp->ptr);
		}
		free(twp);
	}
	*lst = NULL;
}
