/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:49:02 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	cd_home(void)
{
	char	*home;

	home = ft_getenv("HOME", g_data()->environ);
	if (!home || chdir(home) == -1)
		return (ft_dprintf(STDERR_FILENO, NAME"cd: HOME not set\n"), false);
	return (true);
}

bool	cd_dash(t_cmd *cmd)
{
	char	*oldpwd;

	if (ft_strlen(cmd->argv[1]) > 1)
		return (ft_dprintf(STDERR_FILENO, NAME"cd: %s: invalid option\n",
				cmd->argv[1]), ft_printf("cd: usage: cd [-] [dir]\n"), false);
	oldpwd = ft_getenv("OLDPWD", g_data()->environ);
	if (!oldpwd || chdir(oldpwd) == -1)
		return (ft_dprintf(STDERR_FILENO, NAME"cd: OLDPWD not set\n"),
			false);
	ft_printf("%s\n", ft_getenv("OLDPWD", g_data()->environ));
	return (true);
}

bool	cd_dir(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) == -1)
	{
		if (access(cmd->argv[1], F_OK) == -1)
			return (ft_dprintf(STDERR_FILENO,
					NAME"cd: %s: "NSFOD"\n", cmd->argv[1]), false);
		else
			return (ft_dprintf(STDERR_FILENO,
					NAME"cd: %s: "PD"\n", cmd->argv[1]), false);
	}
	return (true);
}

bool	builtin_cd(t_cmd *cmd)
{
	bool	ret;

	if (cmd->argc > 2)
		return (ft_dprintf(STDERR_FILENO, NAME"cd: too many arguments\n"),
			false);
	else if (cmd->argc == 1)
		ret = cd_home();
	else if (cmd->argc == 2 && cmd->argv[1][0] == '-')
		ret = cd_dash(cmd);
	else
		ret = cd_dir(cmd);
	if (!ret)
		return (g_data()->exit_status = EXIT_FAILURE, false);
	update_pwd(g_data()->environ);
	return (g_data()->exit_status = EXIT_SUCCESS, true);
}
