/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:18:32 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/12 19:18:32 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*curr_node;

	if (lst && del)
	{
		next_node = *lst;
		while (next_node)
		{
			curr_node = next_node;
			next_node = next_node->next;
			ft_lstdelone(curr_node, del);
		}
		*lst = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_node;

	if (!lst)
		return (NULL);
	last_node = lst;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new;
	}
	else
		*lst = new;
}

//char	**get_entries(char	*dirname)
//{
//	DIR				*dir;
//	struct dirent	*entry;
//	char			**entries;
//	bool			empty;
//	int				i;
//
//	empty = false;
//	if (dirname && !dirname[0])
//	{
//		dirname = ".";
//		empty = true;
//	}
//	dir = opendir(dirname);
//	if (!dir)
//		return (NULL);
//	i = 0;
//	while (readdir(dir))
//		i++;
//	entries = malloc(sizeof(char *) * (i + 1));
//	if (!entries)
//		return (NULL);
//	i = 0;
//	closedir(dir);
//	dir = opendir(dirname);
//	if (!dir)
//		return (NULL);
//	entry = readdir(dir);
//	while (entry)
//	{
//		if (entry->d_name[0] != '.')
//		{
//			if (empty)
//				entries[i] = ft_strdup(entry->d_name);
//			else
//				entries[i] = ft_strjoin(dirname, entry->d_name);
//			i++;
//		}
//		entry = readdir(dir);
//	}
//	entries[i] = NULL;
//	sort_2d(entries);
//	closedir(dir);
//	return (entries);
//}

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
	sort_2d(entries);
	closedir(dir);
	return (entries);
}

//char	*ft_2d_to_str(char **entries)
//{
//	int		i;
//	char	*tmp[2];
//	char	*str;
//
//	i = -1;
//	while (entries && entries[++i])
//	{
//		if (entries[i + 1])
//			tmp[0] = ft_strjoin(entries[i], " ");
//		else
//			tmp[0] = ft_strdup(entries[i]);
//		if (i == 0)
//			str = ft_strdup(tmp[0]);
//		else
//		{
//			tmp[1] = ft_strjoin(str, tmp[0]);
//			free(str);
//			str = tmp[1];
//		}
//		free(tmp[0]);
//	}
//	return (str);
//}

char	*get_prefix(char *str, int i)
{
	int		j;
	char	*tmp;

	j = i;
	while (j >= 0 && str[j] != ' ' && str[j] != '\t')
		j--;
	tmp = ft_substr(str, j + 1, i - j - 1);
	return (tmp);
}

char	**get_midfix(char *str, int i)
{
	int		j;
	char	**midfix;
	char	*pattern;

	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	while (str[j] != '*' && j > i)
		j--;
	pattern = ft_substr(str, i + 1, j - i - 1);
	midfix = ft_split(pattern, "*");
	free(pattern);
	return (midfix);
}

char	*get_suffix(char *str, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	k = j;
	while (str[j] != '*' && j > i)
		j--;
	tmp = ft_substr(str, j + 1, k - j - 1);
	return (tmp);
}

char	*ft_lst_to_str(t_list *head)
{
	char	*tmp[2];
	char	*str;

	str = NULL;
	while (head)
	{
		if (head->next)
			tmp[0] = ft_strjoin(head->content, " ");
		else
			tmp[0] = ft_strdup(head->content);
		if (!str)
			str = ft_strdup(tmp[0]);
		else
		{
			tmp[1] = ft_strjoin(str, tmp[0]);
			free(str);
			str = tmp[1];
		}
		free(tmp[0]);
		head = head->next;
	}
	return (str);
}

bool	check_midfix(char *entry, char **midfix)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while (entry && entry[++i])
	{
		if (midfix && midfix[j] && entry[i] == midfix[j][0])
		{
			k = 0;
			while (entry[i + k] == midfix[j][k] && midfix[j][k])
				k++;
			if (!midfix[j][k])
			{
				j++;
				i += k - 1;
			}
		}
	}
	if (midfix && !midfix[j])
		return (true);
	return (false);
}

char	*filter_entries(char **entries, char *prefix, char **midfix,
							char *suffix)
{
	int		i;
	int		j;
	char	*tmp[3];
	t_list	*head;

	head = NULL;
	i = -1;
	while (entries && entries[++i])
	{
		if (*prefix && ft_strncmp(entries[i], prefix, ft_strlen(prefix)) != 0)
			continue ;
		j = ft_strlen(entries[i]) - ft_strlen(suffix);
		if (j < 0)
			j = 0;
		if (*suffix && ft_strncmp(entries[i] + j, suffix,
				ft_strlen(suffix)) != 0)
			continue ;
		tmp[0] = ft_substr(entries[i] + ft_strlen(prefix), 0,
				ft_strlen(entries[i]) - ft_strlen(suffix));
		if (check_midfix(tmp[0], midfix))
		{
			if (entries[i][0] == '.' && prefix[0] != '.')
			{
				free(tmp[0]);
				continue ;
			}
			ft_lstadd_back(&head, ft_lstnew(ft_strdup(entries[i])));
		}
		free(tmp[0]);
	}
	tmp[1] = ft_lst_to_str(head);
	ft_lstclear(&head, free);
	return (tmp[1]);
}

char	*expand_asterisk(char *str)
{
	int		i;
	int		j;
	char	*suffix;
	char	**midfix;
	char	**entries;
	char	*prefix;
	char	*tmp[5];

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '*' && !is_in_quote(str, i))
		{
			prefix = get_prefix(str, i);
			midfix = get_midfix(str, i);
			suffix = get_suffix(str, i);
			entries = get_entries();
			tmp[0] = filter_entries(entries, prefix, midfix, suffix);
			if (!tmp[0])
			{
				free(prefix);
				free_2d(midfix);
				free(suffix);
				free_2d(entries);
				while (str[i] && str[i] != ' ' && str[i] != '\t')
					i++;
				i--;
				continue ;
			}
			tmp[1] = ft_substr(str, 0, i - ft_strlen(prefix));
			j = i + 1;
			while (str[j] && str[j] != ' ' && str[j] != '\t')
				j++;
			tmp[2] = ft_substr(str, j, ft_strlen(str) - j);
			tmp[3] = ft_strjoin(tmp[1], tmp[0]);
			tmp[4] = ft_strjoin(tmp[3], tmp[2]);
			i = ft_strlen(tmp[3]) - 1;
			free(tmp[0]);
			free(tmp[1]);
			free(tmp[2]);
			free(tmp[3]);
			free(prefix);
			free_2d(midfix);
			free(suffix);
			free_2d(entries);
			free(str);
			str = tmp[4];
		}
	}
	return (str);
}

//char	*joinname(char *dirname, char *entry)
//{
//	char	*tmp[2];
//
//	if (*dirname && dirname[ft_strlen(dirname) - 1] != '/')
//		tmp[0] = ft_strjoin(dirname, "/");
//	else
//		tmp[0] = ft_strdup(dirname);
//	tmp[1] = ft_strjoin(tmp[0], entry);
//	free(tmp[0]);
//	return (tmp[1]);
//}

//char	*get_pattern(char *str, int i)
//{
//	int		j;
//	char	*tmp;
//
//	j = i;
//	while (str[j] && str[j] != ' ' && str[j] != '\t' && str[j] != '/')
//		j++;
//	if (str[j] == '/' && str[j++])
//		while (str[j] && str[j] != ' ' && str[j] != '\t')
//			j++;
//	tmp = ft_substr(str, i + 1, j - i - 1);
//	return (tmp);
//}

//int	main(int ac, char **av)
//{
//	char	*str = ac > 1 ? ft_strdup(av[1]) : ft_strdup("");
//	char	*tmp;
//
//	tmp = expand_asterisk(str);
//	printf("%s\n", tmp);
//	free(tmp);
//	return (0);
//}
