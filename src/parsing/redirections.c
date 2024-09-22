/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:40:27 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/19 11:51:05 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_add_in(t_link *link, t_redirection **file)
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

int	ft_add_append(t_link *link, t_redirection **file)
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

int	ft_add_out(t_link *link, t_redirection **file)
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

int	ft_add_heredoc(t_link *link, t_redirection **file)
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
		if (!ft_add_in(link, redirectoin))
			return (0);
		else if (!ft_add_out(link, redirectoin))
			return (0);
		else if (!ft_add_append(link, redirectoin))
			return (0);
		else if (!ft_add_heredoc(link, redirectoin))
			return (0);
		else if (link->identifier == OPEN_PAR || link->identifier == CLOSE_PAR)
			return (0);
		link = link->next;
	}
	return (1);
}
