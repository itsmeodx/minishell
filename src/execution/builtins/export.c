/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:09:50 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 18:56:27 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
bool	print_export(char **env)
{
	int		i;
	char	**key_value;

	env = ft_strdup_2d(env);
	sort_env(env);
	i = -1;
	while (env[++i])
	{
		key_value = var_split(env[i]);
		if (!key_value)
			return (free_2d(env), false);
		ft_printf("declare -x %s", key_value[0]);
		if (key_value[1])
			ft_printf("=\"%s\"", key_value[1]);
		ft_printf("\n");
		free_2d(key_value);
	}
	free_2d(env);
	return (true);
}

static
bool	export_plus(char *key)
{
	char	*values[2];
	char	**key_value;

	key_value = var_split(key);
	if (!key_value)
		return (false);
	values[0] = ft_getenv(key_value[0], g_data()->environ);
	values[1] = ft_strjoin(values[0], key_value[1]);
	if (!values[1])
		return (g_data()->exit_status = 1, free_2d(key_value), false);
	free(key_value[1]);
	key_value[1] = values[1];
	if (is_in_env(key_value[0], g_data()->environ))
		update_env(g_data()->environ, key_value[0], key_value[1]);
	else
		g_data()->environ = addtoenv(g_data()->environ,
			key_value[0], key_value[1]);
	free_2d(key_value);
	return (true);
}

static
bool	export_equal(char *key)
{
	char	**key_value;

	key_value = var_split(key);
	if (!key_value)
		return (false);
	if (is_in_env(key_value[0], g_data()->environ))
		update_env(g_data()->environ, key_value[0], key_value[1]);
	else
		g_data()->environ = addtoenv(g_data()->environ,
			key_value[0], key_value[1]);
	free_2d(key_value);
	return (true);
}

static
bool	is_plus_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '+' && key[i] != '=')
		i++;
	if (key[i] == '+' && key[i + 1] == '=')
		return (true);
	return (false);
}

bool	builtin_export(t_cmd *cmd)
{
	int		i;
	bool	bad_key;

	if (cmd->argc == 1)
		return (print_export(g_data()->environ));
	i = 0;
	while (cmd->argv[++i])
	{
		if (!is_valid_key(cmd->argv[i], &bad_key))
			continue ;
		if (is_plus_key(cmd->argv[i]))
			export_plus(cmd->argv[i]);
		else
			export_equal(cmd->argv[i]);
	}
	return (g_data()->exit_status = bad_key, true);
}
