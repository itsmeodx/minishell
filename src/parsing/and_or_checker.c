/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:07:48 by adam              #+#    #+#             */
/*   Updated: 2024/08/28 07:09:29 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errorn	ft_and_or_checker(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == AND || tmp->identifier == OR)
			tmp = tmp->next;
	}
	return (NONE);
}
