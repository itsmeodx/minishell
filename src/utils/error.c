/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:16:10 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/04 23:26:21 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_error(t_error **list, t_error *node)
{
	t_error	*tmp;

	if (!list)
		return ;
	if (!*list)
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_error	*ft_lstnew_error(t_errorn num_error)
{
	t_error	*node;

	node = malloc(sizeof(t_error));
	node->next = NULL;
	node->error = num_error;
	return (node);
}

void	ft_lstdelone_error(t_error *lst)
{
	if (!lst)
		return ;
	free(lst);
}

void	ft_lstclear_error(t_error **lst)
{
	t_error	*current;
	t_error	*twp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		twp = current;
		current = current->next;
		ft_lstdelone_error(twp);
	}
	*lst = NULL;
}
