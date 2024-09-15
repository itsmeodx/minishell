/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:39:49 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/12 17:43:03 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	is_in_quote(char *str, int i)
{
	int		j;
	int		count;
	char	quote;

	count = 0;
	quote = 0;
	j = -1;
	while (str[++j] && j < i)
	{
		if (str[j] == '\"' || str[j] == '\'')
		{
			if (quote == 0)
				quote = str[j];
			else if (quote == str[j])
			{
				count++;
				quote = 0;
			}
		}
		if (str[j] == quote)
			count++;
	}
	if (count % 2 == 0)
		return (false);
	return (true);
}

int	get_next_quote(char *str, char quote)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == quote)
			return (i);
	}
	return (-1);
}
