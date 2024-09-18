/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:08:39 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/18 12:03:10 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*get_prefix(char *str, int i)
{
	int		j;
	char	*tmp;

	j = i;
	while (j >= 0 && str[j] != ' ' && str[j] != '\t')
		j--;
	tmp = ft_substr(str, j + 1, i - j - 1);
	return (tmp);
}

char	**get_midfix(char *str, int i)
{
	int		j;
	char	**midfix;
	char	*pattern;

	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	while (str[j] != '*' && j > i)
		j--;
	pattern = ft_substr(str, i + 1, j - i - 1);
	midfix = ft_qsplit(pattern, "*");
	free(pattern);
	return (midfix);
}

char	*get_suffix(char *str, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	k = j;
	while (str[j] != '*' && j > i)
		j--;
	tmp = ft_substr(str, j + 1, k - j - 1);
	return (tmp);
}

bool	check_midfix(char *entry, char *prefix, char **midfix, char *suffix)
{
	int		i[3];
	char	*tmp;

	i[0] = -1;
	i[1] = 0;
	tmp = ft_substr(entry + ft_strlen(prefix), 0,
			ft_strlen(entry) - ft_strlen(suffix));
	while (tmp && tmp[++i[0]])
	{
		if (midfix && midfix[i[1]] && tmp[i[0]] == midfix[i[1]][0])
		{
			i[2] = 0;
			while (tmp[i[0] + i[2]] == midfix[i[1]][i[2]] && midfix[i[1]][i[2]])
				i[2]++;
			if (!midfix[i[1]][i[2]])
			{
				i[1]++;
				i[0] += i[2] - 1;
			}
		}
	}
	free(tmp);
	if (midfix && !midfix[i[1]])
		return (true);
	return (false);
}
