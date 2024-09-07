/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:50:16 by adam              #+#    #+#             */
/*   Updated: 2024/09/01 11:19:05 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_each_node(char *input)
{
	int		i;
	char	lock;

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
			{
				if (lock == '\'')
					return (-1);
				else
					return (0);
			}
		}
		i++;
	}
	return (true);
}

t_errorn	ft_check_quotes(t_link *link)
{
	t_link	*tmp;
	int		error;

	tmp = link;
	while (tmp)
	{
		error = ft_check_each_node(tmp->command);
		if (error == -1)
			return (ERROR_SIGNAL_QUOTE);
		else if (error == 0)
			return (ERROR_DOUBLE_QUOTE);
		tmp = tmp->next;
	}
	return (NONE);
}
