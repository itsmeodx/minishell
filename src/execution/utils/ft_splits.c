/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:22:24 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/21 12:22:24 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_count_words(char *str, char *charset)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		if (str[i] && !ft_strchr(charset, str[i]))
			count++;
		while (str[i] && !ft_strchr(charset, str[i]))
			i++;
	}
	return (count);
}

static char	*ft_get_word(char *str, char *charset)
{
	int		i;
	char	tmp[2];
	char	*word[2];

	i = 0;
	while (str[i] && ft_strchr(charset, str[i]))
		i++;
	word[0] = ft_substr(str, i, 1);
	i++;
	tmp[1] = '\0';
	while (str[i] && !ft_strchr(charset, str[i]))
	{
		tmp[0] = str[i];
		word[1] = word[0];
		word[0] = ft_strjoin(word[0], tmp);
		free(word[1]);
		i++;
	}
	return (word[0]);
}

char	**ft_splits(char *str, char *charset)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (ft_count_words(str, charset) + 1));
	if (!array)
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_strchr(charset, str[i]))
			i++;
		if (str[i] && !ft_strchr(charset, str[i]))
		{
			array[j] = ft_get_word(str + i, charset);
			j++;
		}
		while (str[i] && !ft_strchr(charset, str[i]))
			i++;
	}
	array[j] = NULL;
	return (array);
}
