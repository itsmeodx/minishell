/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:58:26 by adam              #+#    #+#             */
/*   Updated: 2024/09/26 18:08:20 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errorn	ft_check_pipe(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == PIPE)
		{
			if (!tmp->next || (tmp->next
					&& (tmp->next->identifier == AND
						|| tmp->next->identifier == OR)))
				return (ERROR_PIPE);
			else if (!tmp->prev || (tmp->prev
					&& (tmp->prev->identifier == AND
						|| tmp->prev->identifier == OR
						|| ft_is_redirection(tmp->prev->identifier))))
				return (ERROR_PIPE);
		}
		tmp = tmp->next;
	}
	return (NONE);
}

t_errorn	ft_check_herdoc(t_link *link)
{
	t_link	*tmp;
	int		num_herdoc;

	tmp = link;
	num_herdoc = 0;
	while (tmp)
	{
		if (tmp->identifier == HEREDOC)
		{
			if (!tmp->next || (tmp->next && (tmp->next->identifier == AND
						|| tmp->next->identifier == OR)))
				return (ERROR_HERDOC);
			num_herdoc++;
			if (num_herdoc > 16)
				return (ERROR_NUM_HERDOC);
		}
		tmp = tmp->next;
	}
	return (NONE);
}

t_errorn	ft_check_append(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == APPEND && (!tmp->next
				|| (tmp->next && (tmp->next->identifier == AND
						|| tmp->next->identifier == OR))))
			return (ERROR_APPEND);
		tmp = tmp->next;
	}
	return (NONE);
}

t_errorn	ft_check_out(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == OUT && (!tmp->next
				|| (tmp->next && (tmp->next->identifier == AND
						|| tmp->next->identifier == OR))))
			return (ERROR_OUT);
		tmp = tmp->next;
	}
	return (NONE);
}

t_errorn	ft_check_in(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == IN && (!tmp->next
				|| (tmp->next && (tmp->next->identifier == AND
						|| tmp->next->identifier == OR))))
			return (ERROR_IN);
		tmp = tmp->next;
	}
	return (NONE);
}
