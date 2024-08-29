/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:20:34 by adam              #+#    #+#             */
/*   Updated: 2024/08/28 00:32:44 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_index_parentheses(char *input)
{
	int	i;
	int	valider;

	valider = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '(')
			valider++;
		else if (input[i] == ')')
			valider--;
	}
	if (valider)
		return (false);
	return (true);
}

t_errorn	ft_check_parentheses(t_link *link)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (ft_index_parentheses(tmp->command) == false)
			return (ERROR_PAREN);
		tmp = tmp->next;
	}
	return (NONE);
}
