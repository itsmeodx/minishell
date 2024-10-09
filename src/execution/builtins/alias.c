/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:03:09 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 19:17:04 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
void	print_aliases(char **aliases)
{
	int		i;
	char	**key_value;

	i = 0;
	while (aliases && aliases[i])
	{
		key_value = var_split(aliases[i]);
		if (key_value)
			ft_dprintf(STDOUT_FILENO,
				"alias %s='%s'\n", key_value[0], key_value[1]);
		free_2d(key_value);
		i++;
	}
}

static
void	print_alias(char *key, char **aliases, bool *bad_key)
{
	if (is_in_env(key, aliases))
		ft_dprintf(STDOUT_FILENO,
			"alias %s='%s'\n", key,
			ft_getenv(key, aliases));
	else
	{
		ft_dprintf(STDOUT_FILENO,
			NAME"alias: %s: not found\n", key);
		*bad_key = true;
	}
}

static
bool	check_alias(char *key)
{
	int			i;
	static char	forbidden[] = " &|;<>$(){}\\\"'`\t\n\r\v\f";

	i = 0;
	while (forbidden[i])
	{
		if (ft_strchr(key, forbidden[i]))
			return (false);
		i++;
	}
	return (true);
}

static
void	set_alias(char **key_value, char ***aliases, bool *bad_key)
{
	if (!check_alias(key_value[0]))
	{
		*bad_key = true;
		ft_printf(NAME"alias: %s: " IAN "\n", key_value[0]);
	}
	else if (is_in_env(key_value[0], *aliases))
		update_env(*aliases, key_value[0], key_value[1]);
	else
		*aliases = addtoenv(*aliases, key_value[0], key_value[1]);
}

bool	builtin_alias(t_cmd *cmd)
{
	int		i;
	bool	bad_key;
	char	**key_value;

	i = 0;
	if (cmd->argc == 1)
		return (print_aliases(g_data()->aliases), true);
	bad_key = false;
	while (cmd->argv && cmd->argv[++i])
	{
		key_value = var_split(cmd->argv[i]);
		if (!key_value)
			return (g_data()->exit_status = 1, false);
		if (!key_value[1])
			print_alias(key_value[0], g_data()->aliases, &bad_key);
		else
			set_alias(key_value, &g_data()->aliases, &bad_key);
		free_2d(key_value);
	}
	return (g_data()->exit_status = bad_key, true);
}
