/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 13:15:24 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	cd_home(void)
{
	if (chdir(ft_getenv("HOME")) == -1)
		return (dprintf(STDERR_FILENO, NAME"cd: HOME not set\n"), false);
	return (true);
}

bool	cd_tilde(t_cmd *cmd)
{
	int		i;
	char	*home;
	char	*path;

	i = 1;
	if (cmd->argv[1][0] == '~' && cmd->argv[1][1] == '~')
		return (dprintf(STDERR_FILENO, NAME"cd: %s: "NSFOD"\n",
				cmd->argv[1]), false);
	home = ft_getenv("HOME");
	if (!home)
		return (dprintf(STDERR_FILENO, NAME"cd: HOME not set\n"), false);
	home = ft_strjoin(home, "/");
	while (cmd->argv[1][i] == '/')
		i++;
	path = ft_strjoin(home, cmd->argv[1] + i);
	free(home);
	if (!path)
		return (false);
	if (chdir(path) == -1)
		return (dprintf(STDERR_FILENO, NAME"cd: %s: "NSFOD"\n", path),
			free(path), false);
	free(path);
	return (true);
}

bool	cd_dash(t_cmd *cmd)
{
	char	*oldpwd;

	if (strlen(cmd->argv[1]) > 1)
		return (dprintf(STDERR_FILENO, NAME"cd: %s: invalid option\n",
				cmd->argv[1]), printf("cd: usage: cd [-] [dir]\n"), false);
	oldpwd = ft_getenv("OLDPWD");
	if (chdir(oldpwd) == -1)
		return (dprintf(STDERR_FILENO, NAME"cd: OLDPWD not set\n"),
			false);
	printf("%s\n", ft_getenv("OLDPWD"));
	return (true);
}

bool	cd_dir(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) == -1)
	{
		if (access(cmd->argv[1], F_OK) == -1)
			return (dprintf(STDERR_FILENO,
					NAME"cd: %s: "NSFOD"\n", cmd->argv[1]), false);
		else
			return (dprintf(STDERR_FILENO,
					NAME"cd: %s: "PD"\n", cmd->argv[1]), false);
	}
	return (true);
}

bool	builtin_cd(t_cmd *cmd)
{
	if (cmd->argc > 2)
		return (dprintf(STDERR_FILENO, NAME"cd: too many arguments\n"),
			false);
	else if (cmd->argc == 1)
	{
		if (!cd_home())
			return (false);
	}
	else if (cmd->argc == 2 && cmd->argv[1][0] == '~')
	{
		if (!cd_tilde(cmd))
			return (false);
	}
	else if (cmd->argc == 2 && cmd->argv[1][0] == '-')
	{
		if (!cd_dash(cmd))
			return (false);
	}
	else if (cmd->argc == 2)
	{
		if (!cd_dir(cmd))
			return (false);
	}
	update_pwd(g_data.environ);
	return (true);
}
