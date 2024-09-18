/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:17:07 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/18 13:08:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen_2d(char **s)
{
	int	counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[counter])
		counter++;
	return (counter);
}

char	**ft_strdup_2d(char **ptr)
{
	char	**put;
	int		size;
	size_t	i;

	i = 0;
	if (!ptr)
		return (NULL);
	size = ft_strlen_2d(ptr);
	put = malloc(sizeof(char *) * (size + 1));
	if (!put)
		return (0);
	while (ptr[i])
	{
		put[i] = ft_strdup(ptr[i]);
		i++;
	}
	put[i] = NULL;
	return (put);
}
