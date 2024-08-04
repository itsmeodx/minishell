/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:16:23 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/04 23:26:21 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **tab, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(src);
	if (size == 0)
		return (l);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, l1 + 1);
	ft_strlcpy(p + l1, s2, l2 + 1);
	return (p);
}

char	**ft_strjoin_pro(char **s1, char **s2)
{
	char	**tmp;
	int		i[2];

	i[0] = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (free_str(s1, ft_count_strs(s1)), ft_strdup_pro(s2));
	if (!s2)
		return (ft_strdup_pro(s1));
	tmp = (char **)malloc(sizeof(char *) * (ft_count_strs(s1)
				+ ft_count_strs(s2) + 1));
	while (s1[i[0]])
	{
		tmp[i[0]] = ft_strdup(s1[i[0]]);
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		tmp[i[0]++] = ft_strdup(s2[i[1]++]);
	}
	tmp[i[0]] = NULL;
	free_str(s1, ft_count_strs(s1));
	return (tmp);
}
