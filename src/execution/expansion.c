/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:57:17 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/18 13:08:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*expand_pergola(char *str)
{
	char	*home;
	char	*tmp;

	if (str[1] == '\0' || str[1] == '/')
	{
		home = ft_getenv("HOME");
		if (!home)
			home = get_home();
		if (!home)
			return (dprintf(STDERR_FILENO, NAME "HOME not set\n"), str);
		tmp = ft_strjoin(home, str + 1);
		free(str);
		return (tmp);
	}
	return (str);
}

char	*expand_status(char *str, int *i)
{
	char	*value;

	i[1] = i[0] + 2;
	value = ft_itoa(g_data.exit_status);
	str = expand_val(str, value, i);
	i[0] -= i[2] - 1;
	free(value);
	return (str);
}

int	expand_argv(t_cmd *cmd, int i, char *(*expand_func)(char *))
{
	int		len;
	char	*str;
	char	**tmp[3];

	cmd->argv[i] = expand_func(cmd->argv[i]);
	tmp[0] = ft_qsplit(cmd->argv[i], " \t\v\n\r\f");
	len = ft_strlen_2d(tmp[0]);
	if (len == 1)
		return (free_2d(tmp[0]), i);
	str = cmd->argv[i];
	cmd->argv[i] = NULL;
	tmp[1] = ft_strdup_2d(cmd->argv);
	tmp[1] = ft_strjoin_2d(tmp[1], tmp[0]);
	free_2d(tmp[0]);
	tmp[0] = ft_strjoin_2d(tmp[1], cmd->argv + i + 1);
	cmd->argv[i] = str;
	free_2d(cmd->argv);
	cmd->argv = tmp[0];
	i += len - 1;
	cmd->argc += len - 1;
	return (i);
}

void	ft_expansion(t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->argv && cmd->argv[++i])
	{
		if (cmd->argv[i][0] == '~')
			cmd->argv[i] = expand_pergola(cmd->argv[i]);
		cmd->argv[i] = expand_asterisk(cmd->argv[i]);
		i = expand_argv(cmd, i, &expand_dollar);
		if (i < 0)
			continue ;
		cmd->argv[i] = ft_expanding(cmd->argv[i]);
	}
}
