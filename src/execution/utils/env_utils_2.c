/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:14 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:51:24 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	sort_2d(char **strs)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_strlen_2d(strs);
	while (i--)
	{
		j = 0;
		while (strs[j])
		{
			if (strs[j + 1] && ft_strcmp(strs[j], strs[j + 1]) > 0)
			{
				tmp = strs[j];
				strs[j] = strs[j + 1];
				strs[j + 1] = tmp;
			}
			j++;
		}
	}
}

int	ft_envcmp(char *s1, char *s2)
{
	char	**key_value[2];
	int		i;

	key_value[0] = var_split(s1);
	key_value[1] = var_split(s2);
	i = ft_strcmp(key_value[0][0], key_value[1][0]);
	free_2d(key_value[0]);
	free_2d(key_value[1]);
	return (i);
}

void	sort_env(char **strs)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_strlen_2d(strs);
	while (i--)
	{
		j = 0;
		while (strs[j])
		{
			if (strs[j + 1] && ft_envcmp(strs[j], strs[j + 1]) > 0)
			{
				tmp = strs[j];
				strs[j] = strs[j + 1];
				strs[j + 1] = tmp;
			}
			j++;
		}
	}
}

char	*expand_val(char *str, char *value, int *i)
{
	char	*tmp1;
	char	*tmp2;

	if (value == NULL)
		value = "";
	i[2] = ft_strlen(value);
	tmp1 = ft_substr(str, 0, i[0]);
	tmp2 = ft_strjoin(tmp1, value);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, str + i[1]);
	free(tmp2);
	free(str);
	str = tmp1;
	i[0] += i[2] - 1;
	return (str);
}

char	*expand_dollar(char *str)
{
	int		i[3];
	char	*key;
	char	*value;

	i[0] = -1;
	while (str[++i[0]])
	{
		if (str[i[0]] == '$' && str[i[0] + 1] == '?')
			str = expand_status(str, i);
		else if (str[i[0]] == '$' && str[i[0] + 1] != '$'
			&& (isalnum(str[i[0] + 1]) || str[i[0] + 1] == '_'))
		{
			i[1] = i[0] + 1;
			while (isalnum(str[i[1]]) || str[i[1]] == '_')
				i[1]++;
			key = ft_substr(str, i[0] + 1, i[1] - i[0] - 1);
			value = ft_getenv(key, g_data()->environ);
			free(key);
			str = expand_val(str, value, i);
		}
	}
	return (str);
}
