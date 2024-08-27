/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:44:32 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/27 14:00:13 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	*extend_2d(char **ptr, size_t size)
{
	int		i;
	char	**new;

	if (!ptr)
		return (NULL);
	i = 0;
	while (ptr[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1 + size));
	if (!new)
		return (NULL);
	i = -1;
	while (ptr[++i])
		new[i] = ptr[i];
	while (size--)
		new[i++] = NULL;
	free(ptr);
	return (new);
}
