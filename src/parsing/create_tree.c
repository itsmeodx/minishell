/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:41 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/14 10:28:48 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tree	*ft_create_tree(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link  *target;

	if (!link || !tree)
		return (NULL);
	target = ft_find_hightest_proirity(link);
	new = ft_treenew(target->command, target->identifier);
	ft_treeadd_back_left(tree, new);
	if (link->prev)
		ft_create_tree(&(*tree)->left, link->prev);
	else if (link->next)
		ft_create_tree(&(*tree)->right, link->next);
	else if (!link->prev && !link->next)
		return (*tree);
	return (*tree);
}
