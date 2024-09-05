/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:57:17 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/02 17:06:56 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
char	*expand_tilde(char *str)
{
	char	*home;
	char	*tmp;

	if (str[1] == '\0' || str[1] == '/')
	{
		home = ft_getenv("HOME");
		if (!home)
			return (dprintf(STDERR_FILENO, NAME "HOME not set\n"), str);
		tmp = ft_strjoin(home, str + 1);
		free(str);
		return (tmp);
	}
	return (str);
}

static
char	*expandtoval(char *str, char *value, int *i)
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

static
char	*expandtostatus(char *str, int *i)
{
	char	*value;

	i[1] = i[0] + 2;
	value = ft_itoa(g_data.exit_status);
	str = expandtoval(str, value, i);
	i[0] -= i[2] - 1;
	free(value);
	return (str);
}

static
char	*expand_env(char *str)
{
	int		i[3];
	char	*key;
	char	*value;

	i[0] = -1;
	while (str[++i[0]])
	{
		if (str[i[0]] == '$' && str[i[0] + 1] == '?')
			str = expandtostatus(str, i);
		else if (str[i[0]] == '$' && str[i[0] + 1] != '$'
			&& str[i[0] + 1] != ' ' && str[i[0] + 1] != '\0')
		{
			i[1] = i[0] + 1;
			while (isalnum(str[i[1]]) || str[i[1]] == '_')
				i[1]++;
			key = ft_substr(str, i[0] + 1, i[1] - i[0] - 1);
			value = ft_getenv(key);
			free(key);
			str = expandtoval(str, value, i);
		}
	}
	return (str);
}

void	ft_expansion(char **str)
{
	int		i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i][0] == '~')
			str[i] = expand_tilde(str[i]);
		str[i] = expand_env(str[i]);
	}
}
