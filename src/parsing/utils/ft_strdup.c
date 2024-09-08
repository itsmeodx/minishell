/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:17:07 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/08 12:32:02 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_strs(char **s)
{
	int	counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[counter])
		counter++;
	return (counter);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	char	*put;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = (char *)s;
	put = malloc(ft_strlen(s) + 1);
	if (put == NULL)
		return (NULL);
	while (ptr[i])
	{
		put[i] = ptr[i];
		i++;
	}
	put[i] = '\0';
	return (put);
}

char	**ft_strdup_2d(char **ptr)
{
	char	**put;
	int		size;
	size_t	i;

	i = 0;
	size = ft_count_strs(ptr);
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
