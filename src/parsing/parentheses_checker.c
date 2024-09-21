/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:20:34 by adam              #+#    #+#             */
/*   Updated: 2024/09/21 15:01:29 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_index_parentheses(t_link *link)
{
	int		valider;
	t_link	*tmp;

	tmp = link;
	valider = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->command, "(", ft_strlen(tmp->command)) == 0)
			valider++;
		else if (ft_strncmp(tmp->command, ")", ft_strlen(tmp->command)) == 0)
			valider--;
		tmp = tmp->next;
	}
	if (valider > 0)
		return (ERROR_OPEN_PAREN);
	else if (valider < 0)
		return (ERROR_CLOSE_PAREN);
	else
		return (NONE);
}

int	ft_void_parentheses(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == OPEN_PAR && (tmp->next
				&& tmp->next->identifier == CLOSE_PAR))
			return (ERROR_CLOSE_PAREN);
		tmp = tmp->next;
	}
	return (NONE);
}

int	ft_before_parentheses(t_link *link)
{
	while (link)
	{
		if (link->identifier == OPEN_PAR && link->prev
			&& (link->prev->identifier == STR
				|| ft_is_redirection(link->prev->identifier)))
			return (ERROR_OPEN_PAREN);
		link = link->next;
	}
	return (NONE);
}

t_errorn	ft_check_parentheses(t_link *link)
{
	int	error;

	error = ft_index_parentheses(link);
	if (error)
		return (error);
	error = ft_void_parentheses(link);
	if (error)
		return (ERROR_CLOSE_PAREN);
	error = ft_before_parentheses(link);
	if (error)
		return (error);
	return (NONE);
}
