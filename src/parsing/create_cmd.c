/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:52:55 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/31 19:08:18 by akhobba          ###   ########.fr       */
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
	free_2d(tmp);
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
