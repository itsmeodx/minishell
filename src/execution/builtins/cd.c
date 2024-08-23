/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/12 16:09:21 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_strjoin(char *s1, char *s2);

bool	cd_home(void)
{
	if (chdir(getenv("HOME")) == -1)
		return (dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"), false);
	return (true);
}

bool	cd_tilde(t_cmd *cmd)
{
	int		i;
	char	*home;
	char	*path;

	i = 1;
	if (cmd->argv[1][0] == '~' && cmd->argv[1][1] == '~')
		return (dprintf(STDERR_FILENO, "minishell: cd: %s: "NSFOD"\n",
				cmd->argv[1]), false);
	home = getenv("HOME");
	if (!home)
		return (dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"), false);
	home = ft_strjoin(home, "/");
	while (cmd->argv[1][i] == '/')
		i++;
	path = ft_strjoin(home, cmd->argv[1] + i);
	free(home);
	if (!path)
		return (false);
	if (chdir(path) == -1)
		return (dprintf(STDERR_FILENO, "minishell: cd: %s: "NSFOD"\n", path),
			free(path), false);
	free(path);
	return (true);
}

bool	cd_dash(t_cmd *cmd)
{
	char	*oldpwd;

	if (strlen(cmd->argv[1]) > 1)
		return (dprintf(STDERR_FILENO, "minishell: cd: %s: invalid option\n",
				cmd->argv[1]), printf("cd: usage: cd [-] [dir]\n"), false);
	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
		return (dprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n"),
			false);
	if (chdir(oldpwd) == -1)
		return (dprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n"),
			false);
	printf("%s\n", getenv("OLDPWD"));
	return (true);
}

bool	cd_dir(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) == -1)
	{
		if (access(cmd->argv[1], F_OK) == -1)
			return (dprintf(STDERR_FILENO,
					"minishell: cd: %s: "NSFOD"\n", cmd->argv[1]), false);
		else
			return (dprintf(STDERR_FILENO,
					"minishell: cd: %s: "PD"\n", cmd->argv[1]), false);
	}
	return (true);
}

bool	builtin_cd(t_cmd *cmd)
{
	if (cmd->argc > 2)
		return (dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n"),
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
	return (true);
}
