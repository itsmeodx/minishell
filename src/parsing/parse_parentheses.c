/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:59:39 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/25 10:59:11 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_link	*ft_limit_link(t_link **link)
{
	t_link	*tmp;
	t_link	*last;

	if (!link || !*link)
		return (NULL);
	tmp = ft_dbl_lstlast(*link);
	last = NULL;
	while (tmp)
	{
		if (tmp->identifier == CLOSE_PAR
			&& (!tmp->next || tmp->next->identifier != CLOSE_PAR))
		{
			last = tmp->next;
			tmp->prev->next = NULL;
			break ;
		}
		tmp = tmp->prev;
	}
	return (last);
}

t_tree	*ft_parse_parenthesis(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link	*last;

	new = NULL;
	last = ft_limit_link(&link);
	if (!tree)
		return (NULL);
	if (!link)
		return (*tree);
	new = ft_parse_and_or(link);
	if (new)
		ft_treeadd_back_left(tree, new);
	if (last)
		ft_treeadd_back_right(tree, ft_parse_and_or(last));
	return (*tree);
}
