/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:17:07 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/04 23:26:21 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	put = (char *)malloc(ft_strlen(s) + 1);
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

char	**ft_strdup_pro(char **ptr)
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
