/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:55 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/27 12:39:06 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_to_argv(t_tree **new, char *command)
{
	char	**tmp;

	if (!command)
		return ;
	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup(command);
	tmp[1] = NULL;
	(*new)->cmd->argv = ft_strjoin_2d((*new)->cmd->argv, tmp);
	(*new)->cmd->argc++;
}

void	ft_cmd_create(t_tree **new, t_link *link)
{
	while (link)
	{
		if (link->prev->identifier == STR && link->identifier == STR)
		{
			ft_add_to_argv(new, link->command);
		}
		link = link->next;
	}
}
