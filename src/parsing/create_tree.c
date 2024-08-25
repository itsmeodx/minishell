/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:41 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/25 11:41:51 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tree	*ft_parse_cmd(t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = STR;
	goal[1] = OPEN_PAR;
	if (!link)
		return (NULL);
	target = ft_search_target(link, goal);
	if (!target)
		return (NULL);
	new = ft_treenew(target->command, target->identifier);
	if (link->next)
	{
		ft_cmd_create(&new, link->next);
		ft_redirections(link->next, &new->redirection);
	}
	if (target->identifier == OPEN_PAR)
		ft_parse_parenthesis(&new, link->next);
	return (new);
}

t_tree	*ft_parse_pipe(t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = PIPE;
	goal[1] = LEN_ENUM + 2;
	if (!link)
		return (NULL);
	target = ft_search_target(link, goal);
	if (!target)
	{
		new = ft_parse_cmd(link);
		return (new);
	}
	new = ft_treenew(target->command, target->identifier);
	if (target->prev)
	{
		target->prev->next = NULL;
		ft_treeadd_back_left(&new, ft_parse_cmd(link));
	}
	if (target->next)
		ft_treeadd_back_right(&new, ft_parse_pipe(target->next));
	return (new);
}

t_tree	*ft_parse_and_or(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = OR;
	goal[1] = AND;
	tree = NULL;
	if (!link)
		return (NULL);
	target = ft_search_target(link, goal);
	if (!target)
	{
		new = ft_parse_pipe(link);
		return (new);
	}
	new = ft_treenew(target->command, target->identifier);
	if (target->prev)
	{
		target->prev->next = NULL;
		ft_treeadd_back_left(&new, ft_parse_pipe(link));
	}
	if (target->next)
		ft_treeadd_back_right(&new, ft_parse_and_or(&new, target->next));
	return (new);
}

t_tree	*ft_create_tree(t_tree **tree, t_link *link)
{
	*tree = ft_parse_and_or(tree, link);
	return (*tree);
}
