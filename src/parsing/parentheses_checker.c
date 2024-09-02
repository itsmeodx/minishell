/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:20:34 by adam              #+#    #+#             */
/*   Updated: 2024/09/01 11:31:59 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_index_parentheses(t_link *link)
{
	int	i;
	int	valider;
	t_link	*tmp;

	tmp = link;
	valider = 0;
	i = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->command, "(", ft_strlen(tmp->command)) == 0)
			valider++;
		else if (ft_strncmp(tmp->command, ")", ft_strlen(tmp->command)) == 0)
			valider--;
		tmp = tmp->next;
	}
	if (valider > 0)
		return (0);
	else if (valider < 0)
		return (-1);
	else
		return (true);
}

t_errorn	ft_check_parentheses(t_link *link)
{
	int 	error;

	error = ft_index_parentheses(link);
	if (error == 0)
		return (ERROR_OPEN_PAREN);
	if (error == -1)
		return (ERROR_CLOSE_PAREN);
	return (NONE);
}
