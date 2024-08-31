/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:50:16 by adam              #+#    #+#             */
/*   Updated: 2024/08/31 16:48:23 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_each_node(char *input)
{
	int i;
	char lock;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			lock = input[i];
			while (input[++i])
			{
				if (input[i] == lock)
					break ;
			}
			if (input[i] == '\0')
				return (false);
		}
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
