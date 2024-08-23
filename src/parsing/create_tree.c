/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:41 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/23 11:15:14 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tree	*ft_parse_cmd(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = STR;
	goal[1] = LEN_ENUM;
	if (!tree)
		return (NULL);
	if (!link)
		return (*tree);
	target = ft_search_target(link, goal);
	if (!target)
		return (NULL); // bad interpretation
	new = ft_treenew(target->command, target->identifier);
	if (!*tree)
		*tree = new;
	if (link->next)
	{
		ft_cmd_create(&new, link->next);
		ft_redirections(link->next, &new->redirection);
	}
	return (new);
}

t_tree	*ft_parse_pipe(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = PIPE;
	goal[1] = LEN_ENUM;
	if (!tree)
		return (NULL);
	if (!link)
		return (*tree);
	target = ft_search_target(link, goal);
	if (!target)
		return (ft_parse_cmd(tree, link));
	new = ft_treenew(target->command, target->identifier);
	if (!*tree)
		*tree = new;
	if (target->prev)
	{
		target->prev->next = NULL;
		ft_treeadd_back_left(&new, ft_parse_cmd(&new, link));
	}
	if (target->next)
		ft_treeadd_back_right(&new, ft_parse_pipe(&new, target->next));
	return (new);
}

t_tree	*ft_parse_and_or(t_tree **tree, t_link *link)
{
	t_tree	*new;
	t_link	*target;
	int		goal[2];

	goal[0] = OR;
	goal[1] = AND;
	if (!tree)
		return (NULL);
	if (!link)
		return (*tree);
	target = ft_search_target(link, goal);
	if (!target)
		return (ft_parse_pipe(tree, link));
	new = ft_treenew(target->command, target->identifier);
	if (!*tree)
		*tree = new;
	if (target->prev)
	{
		target->prev->next = NULL;
		ft_treeadd_back_left(&new, ft_parse_pipe(&new, link));
	}
	if (target->next)
		ft_treeadd_back_right(&new, ft_parse_and_or(&new, target->next));
	return (new);
}

t_tree	*ft_create_tree(t_tree **tree, t_link *link)
{
	ft_parse_and_or(tree, link);
	return (*tree);
}
