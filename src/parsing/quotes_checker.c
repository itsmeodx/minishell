/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:50:16 by adam              #+#    #+#             */
/*   Updated: 2024/08/31 12:55:41 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_each_node(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		i++;
	}
	return (true);
}

t_errorn	ft_check_quotes(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (ft_check_each_node(tmp->command) == false)
			return (ERROR_QUOTE);
		tmp = tmp->next;
	}
	return (NONE);
}
