/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/11 12:46:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	cd_home(void)
{
	if (chdir(getenv("HOME")) == -1)
		return (dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"), false);
	return (true);
}

bool	cd_tilde(t_cmd *cmd)
{
	if (chdir(getenv("HOME")) == -1)
		return (dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n"), false);
	if (chdir(cmd->argv[1] + 2) == -1)
		return (dprintf(STDERR_FILENO,
				"minishell: cd: %s%s: no such file or directory\n",
				getenv("HOME"), cmd->argv[1] + 1), false);
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
		return (dprintf(STDERR_FILENO,
				"minishell: cd: %s: no such file or directory\n", cmd->argv[1]),
			false);
	return (true);
}

bool	cd(t_cmd *cmd)
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
	update_env("PWD", getcwd(NULL, 0));
	return (true);
}

/*
int	main(int argc, char **argv)
{
	t_cmd	cmd;

	cmd.argc = argc;
	cmd.argv = argv;
	cd(&cmd);
	return (0);
}
*/