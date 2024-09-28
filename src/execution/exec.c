/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:28:01 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:49:31 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
char	**paths_split(char *path)
{
	int		i;
	char	*tmp;
	char	**paths;

	if (!path)
		return (NULL);
	i = -1;
	paths = ft_qsplit(path, ":");
	while (paths && paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	return (paths);
}

int	ft_execvpe(char *file, char **argv, char **env)
{
	int		i;
	char	*path;
	char	**paths;

	paths = paths_split(ft_getenv("PATH", env));
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], file);
		execve(path, argv, env);
		free(path);
	}
	free_2d(paths);
	return (-1);
}
