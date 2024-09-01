/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:28:01 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 13:28:01 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static char	**paths_split(char *path)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = -1;
	paths = ft_split(path, ":");
	while (paths && paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	return (paths);
}

int	ft_execvp(char *file, char **argv)
{
	int		i;
	char	*path;
	char	**paths;

	paths = paths_split(ft_getenv("PATH"));
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], file);
		execve(path, argv, g_data.environ);
		free(path);
	}
	free_2d(paths);
	return (-1);
}
