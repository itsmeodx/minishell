/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:52 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/11 20:45:58 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_lstadd_back_redi(t_redirection **list, t_redirection *node)
{
	t_redirection	*tmp;

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

t_redirection	*ft_lstnew_redi(char *content)
{
	t_redirection	*node;

	node = malloc(sizeof(t_redirection));
	if (node == NULL)
		return (NULL);
	node->file = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_lstdelone_redi(t_redirection *lst)
{
	if (!lst)
		return ;
	free(lst);
}

void	ft_lstclear_redi(t_redirection **lst)
{
	t_redirection	*current;
	t_redirection	*twp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		twp = current;
		current = current->next;
		free(twp->file);
		ft_lstdelone_redi(twp);
	}
	*lst = NULL;
}
