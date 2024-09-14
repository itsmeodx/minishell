/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:40:27 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/13 17:52:18 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_less(t_link *link, t_redirection **file)
{
	t_redirection	*node;

	if (link->identifier == IN)
	{
		if (link->next && link->next->identifier == STR)
		{
			node = ft_lstnew_redi(link->next->command);
			node->identifier = IN;
			ft_lstadd_back_redi(file, node);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

int	ft_check_lessless(t_link *link, t_redirection **file)
{
	t_redirection	*node;

	if (link->identifier == APPEND)
	{
		if (link->next && link->next->identifier == STR)
		{
			node = ft_lstnew_redi(link->next->command);
			node->identifier = APPEND;
			ft_lstadd_back_redi(file, node);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

int	ft_check_great(t_link *link, t_redirection **file)
{
	t_redirection	*node;

	if (link->identifier == OUT)
	{
		if (link->next && link->next->identifier == STR)
		{
			node = ft_lstnew_redi(link->next->command);
			node->identifier = OUT;
			ft_lstadd_back_redi(file, node);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

int	ft_check_greatgreat(t_link *link, t_redirection **file)
{
	t_redirection	*node;

	if (link->identifier == HEREDOC)
	{
		if (link->next && link->next->identifier == STR)
		{
			node = ft_lstnew_redi(link->next->command);
			node->identifier = HEREDOC;
			node->fd = link->fd;
			ft_lstadd_back_redi(file, node);
			return (1);
		}
		else
			return (0);
	}
	return (1);
}

int	ft_redirections(t_link *link, t_redirection **redirectoin)
{
	*redirectoin = NULL;
	while (link)
	{
		if (link->identifier == PIPE)
			return (1);
		if (!ft_check_less(link, redirectoin))
			return (0);
		else if (!ft_check_great(link, redirectoin))
			return (0);
		else if (!ft_check_lessless(link, redirectoin))
			return (0);
		else if (!ft_check_greatgreat(link, redirectoin))
			return (0);
		link = link->next;
	}
	return (1);
}
