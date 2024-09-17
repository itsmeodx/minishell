/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:14 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/13 09:53:30 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	sort_2d(char **strs)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (strs[++i])
	{
		j = i;
		while (strs[++j])
		{
			if (strcmp(strs[i], strs[j]) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[j];
				strs[j] = tmp;
			}
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
		if (str[i[0]] == '$')
		{
			if (is_in_quote(str, i[0]) == '\'')
				continue ;
			if (str[i[0] + 1] == '?')
				str = expand_status(str, i);
			else if (str[i[0] + 1] != '$'
				&& (isalnum(str[i[0] + 1]) || str[i[0] + 1] == '_'))
			{
				i[1] = i[0] + 1;
				while (isalnum(str[i[1]]) || str[i[1]] == '_')
					i[1]++;
				key = ft_substr(str, i[0] + 1, i[1] - i[0] - 1);
				value = ft_getenv(key);
				free(key);
				str = expand_val(str, value, i);
			}
		}
	}
	return (str);
}
