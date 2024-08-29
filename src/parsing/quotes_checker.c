/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:50:16 by adam              #+#    #+#             */
/*   Updated: 2024/08/27 22:55:25 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_min(int a, int b)
{
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (a >= b)
		return (b);
	else
		return (a);
}

char	ft_char(int a, int b, char c_a, char c_b)
{
	if (!a)
		return (c_b);
	if (!b)
		return (c_a);
	if (a >= b)
		return (c_b);
	else
		return (c_a);
}

long	ft_index_quote(char *input)
{
	char	c;
	int		start;
	int		start_2;
	int		end;
	long	bin;

	start = ft_strchr('\"', input);
	start_2 = ft_strchr('\'', input);
	if (!start && !start_2)
		return (-1);
	c = ft_char(start, start_2, '\"', '\'');
	start = ft_min(start, start_2);
	end = ft_strchr(c, input + start);
	start--;
	if (!end)
		return (0);
	bin = start;
	bin <<= 32;
	bin += end;
	return (bin);
}

bool	ft_check_each_node(char *input)
{
	long	bin;
	int		start;
	int		end;

	bin = ft_index_quote(input);
	if (!bin || bin == -1)
		return (false);
	start = bin >> 32;
	printf("start=%d\n", start);
	end = bin;
	printf("end=%d\n", end);
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
