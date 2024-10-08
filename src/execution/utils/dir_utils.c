/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:55:17 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/18 12:07:45 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	isdir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (true);
	return (false);
}

int	dir_size(char *dirname)
{
	int				i;
	DIR				*dir;

	dir = opendir(dirname);
	if (!dir)
		return (0);
	i = 0;
	while (readdir(dir))
		i++;
	closedir(dir);
	return (i);
}

void	sort_2d_case(char **strs)
{
	int		i;
	char	*tmp;

	i = -1;
	while (strs && strs[++i])
	{
		if (strs[i + 1] && ft_strcasecmp(strs[i], strs[i + 1]) > 0)
		{
			tmp = strs[i];
			strs[i] = strs[i + 1];
			strs[i + 1] = tmp;
			i = -1;
		}
	}
}

char	**get_entries(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**entries;
	int				i;

	i = dir_size(".");
	entries = malloc(sizeof(char *) * (i + 1));
	if (!entries)
		return (NULL);
	i = 0;
	dir = opendir(".");
	if (!dir)
		return (free(entries), NULL);
	entry = readdir(dir);
	while (entry)
	{
		entries[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	entries[i] = NULL;
	sort_2d_case(entries);
	closedir(dir);
	return (entries);
}
