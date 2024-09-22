/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstexpand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:23:44 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/22 22:24:38 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	ft_lstexpand(t_list **lst, char id, char *str)
{
	char	*tmp;

	if (id == '\"')
		str = expand_dollar(str);
	else if (id == '\0')
	{
		str = expand_pergola(str);
		str = expand_dollar(str);
		str = expand_asterisk(str);
	}
	if (id == '\"' || id == '\'')
		tmp = ft_strjoin(str, "00");
	else
		tmp = ft_strjoin(str, "01");
	tmp[ft_strlen(tmp) - 2] = 0;
	free(str);
	str = tmp;
	if (*str)
		ft_lstadd_back(lst, ft_lstnew(str));
	else
		free(str);
}

char	**array_split(t_list *lst, char **array)
{
	if (((char *)lst->content)[ft_strlen((char *)lst->content) + 1] == '1')
		array = ft_splits((char *)lst->content, " \t\n");
	else
		array = ft_strdup_2d((char *[]){(char *)lst->content, NULL});
	return (array);
}

void	merge_arrays(char ***array, int *i, char **array1)
{
	char	*tmp;

	tmp = ft_strjoin((*array)[*i], array1[0]);
	free((*array)[*i]);
	(*array)[*i] = tmp;
	*array = ft_strjoin_2d(*array, array1 + 1);
	*i += ft_strlen_2d(array1) - 1;
}

char	**lst_to_argv(t_list *lst)
{
	int		i;
	char	**array[2];

	array[0] = NULL;
	i = 0;
	while (lst)
	{
		array[1] = array_split(lst, array[1]);
		if (!array[0])
		{
			array[0] = ft_strjoin_2d(array[0], array[1]);
			i = ft_strlen_2d(array[1]) - 1;
		}
		else
			merge_arrays(&array[0], &i, array[1]);
		free_2d(array[1]);
		lst = lst->next;
	}
	return (array[0]);
}
