/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:59:39 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/24 21:00:03 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_limit_link(t_link **link)
{
	t_link	*tmp;

	tmp = *link;
	while (tmp)
	{
		if (tmp->identifier == CLOSE_PAR)
			tmp->prev->next = NULL;
		break ;
		tmp = tmp->next;
	}
}

t_tree	*ft_parse_parenthesis(t_tree **tree, t_link *link)
{
	t_tree	*new;

	new = NULL;
	if (!tree)
		return (NULL);
	if (!link)
		return (*tree);
	ft_parse_and_or(&new, link);
	if (new)
		ft_treeadd_back_left(tree, new);
	return (*tree);
}
