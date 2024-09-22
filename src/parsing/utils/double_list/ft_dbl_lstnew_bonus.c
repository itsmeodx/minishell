/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_lstnew_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:36:31 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/13 16:43:55 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_link	*ft_dbl_lstnew(void *content)
{
	t_link	*node;

	node = malloc(sizeof(t_link));
	if (node == NULL)
		return (NULL);
	node->command = ft_strdup(content);
	node->next = NULL;
	node->prev = NULL;
	node->fd = -1;
	ft_garbage_new(node);
	return (node);
}
