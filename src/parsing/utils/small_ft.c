/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:16:23 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/18 13:08:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_strjoin_2d(char **s1, char **s2)
{
	char	**tmp;
	int		i[2];

	i[0] = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_2d(s2));
	if (!s2)
		return (tmp = ft_strdup_2d(s1), free_2d(s1), tmp);
	tmp = (char **)malloc(sizeof(char *) * (ft_strlen_2d(s1)
				+ ft_strlen_2d(s2) + 1));
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
	free_2d(s1);
	return (tmp);
}
