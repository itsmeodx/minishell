/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:28:11 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/21 11:28:27 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_lst_to_str(t_list *head, bool flag)
{
	char	*tmp[2];
	char	*str;

	str = NULL;
	while (head)
	{
		if (head->next && flag)
			tmp[0] = ft_strjoin(head->content, " ");
		else
			tmp[0] = ft_strdup(head->content);
		if (!str)
			str = ft_strdup(tmp[0]);
		else
		{
			tmp[1] = ft_strjoin(str, tmp[0]);
			free(str);
			str = tmp[1];
		}
		free(tmp[0]);
		head = head->next;
	}
	return (str);
}
