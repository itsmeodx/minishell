/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:41 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/24 21:44:51 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_not_command(t_tree **new, t_link *target)
{
	if (target->prev && ft_is_redirection(target->prev->identifier))
		*new = ft_treenew(NULL, STR);
	else
		*new = ft_treenew(target->command, target->identifier);
}

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
	{
		return (NULL);
	}
	ft_not_command(&new, target);
	if (link->next && target->identifier != OPEN_PAR)
	{
		ft_cmd_create(&new, link->next);
		ft_redirections(link, &new->redirections);
	}
	if (target->identifier == OPEN_PAR)
	{
		ft_parse_parenthesis(&new, link->next);
	}
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

t_tree	*ft_parse_and_or(t_link *link)
{
	t_tree		*new;
	t_link		*target;
	static int	goal[2] = {OR, AND};

	if (!link)
		return (NULL);
	target = ft_search_target_rev(link, goal);
	if (!target)
	{
		new = ft_parse_pipe(link);
		return (new);
	}
	new = ft_treenew(target->command, target->identifier);
	if (target->prev)
	{
		target->prev->next = NULL;
		ft_treeadd_back_left(&new, ft_parse_and_or(link));
	}
	if (target->next)
	{
		target->next->prev = NULL;
		ft_treeadd_back_right(&new, ft_parse_pipe(target->next));
	}
	return (new);
}
