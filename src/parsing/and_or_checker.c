/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:07:48 by adam              #+#    #+#             */
/*   Updated: 2024/08/31 12:51:01 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errorn	ft_check_operatore(t_link *link, t_type target, t_errorn error)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == target
			&& ((tmp->prev && tmp->prev->identifier != STR)
			|| (tmp->next && tmp->next->identifier != STR)))
			return (error);
		tmp = tmp->next;
	}
	return (NONE);
}

t_errorn	ft_and_or_checker(t_link *link)
{
	t_errorn	error;

	error = ft_check_operatore(link, AND, ERROR_AND);
	if (error)	
		return (error);
	error = ft_check_operatore(link, OR, ERROR_OR);
	if (error)	
		return (error);
	return (NONE);
}
