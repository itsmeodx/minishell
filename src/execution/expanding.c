/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:59:07 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/26 18:11:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*expand_pergola(char *str)
{
	char	*home;
	char	*tmp;

	if (str[0] == '~' && (str[1] == '\0' || str[1] == '/'))
	{
		home = ft_getenv("HOME");
		if (!home)
			home = get_home();
		if (!home)
			return (ft_dprintf(STDERR_FILENO, NAME "HOME not set\n"), str);
		tmp = ft_strjoin(home, str + 1);
		free(str);
		return (tmp);
	}
	return (str);
}

char	*expand_status(char *str, int *i)
{
	char	*value;

	i[1] = i[0] + 2;
	value = ft_itoa(g_data()->exit_status);
	str = expand_val(str, value, i);
	i[0] -= i[2] - 1;
	free(value);
	return (str);
}

void	handle_quotes(t_list **lst, char *str, int *i)
{
	int	j;

	j = *i - (*i - 1 >= 0);
	while (j > 0 && (str[j - (j > 0)] != '\'' && str[j] != '\'')
		&& (str[j - (j > 0)] != '\"' && str[j] != '\"'))
		j--;
	if (*i != 0)
		ft_lstexpand(lst, 0,
			ft_substr(str, j, *i - j - (str[j] == '\'' || str[j] == '\"')));
	ft_lstexpand(lst, str[*i], ft_subquote(str, *i));
	*i += get_next_quote(str + *i + 1, str[*i]) + 1;
}

void	ft_expanding(t_list **lst, char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			handle_quotes(lst, str, &i);
	}
	j = i;
	while (j > 0 && str[j] != '\'' && str[j] != '\"')
		j--;
	if (!((str[j] == '\'' && j == i - 1) || (str[j] == '\"' && j == i - 1)))
		ft_lstexpand(lst, 0, ft_substr(str,
				j + (str[j] == '\'' || str[j] == '\"'), i - j));
	free(str);
}
