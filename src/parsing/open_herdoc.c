/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:46 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/05 09:39:30 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_open_herdoc(t_link *link)
{
	t_link	*tmp;
	char 	*limit;

	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == HERDOC)
		{

			limit = tmp->next->command;
		}
		tmp = tmp->next;
	}




	return (true);
}
