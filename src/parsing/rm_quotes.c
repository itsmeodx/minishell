/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:20 by adam              #+#    #+#             */
/*   Updated: 2024/09/19 11:07:14 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_name_file(int num_file)
{
	char	*num;
	char	*file;

	num = ft_itoa(num_file);
	file = ft_strjoin(HEREDOC_PREFIX, num);
	if (access(file, F_OK) == 0)
		unlink(file);
	return (free(num), file);
}

size_t	ft_cal_whitoutquotes(char *str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	if (ft_check_each_node(str) != true)
		return (0);
	while (str[i])
	{
		if (!(str[i] == '"' || str[i] == '\''))
			len++;
		i++;
	}
	return (len);
}

char	*ft_tmp_rmquotes(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ptr = malloc(ft_cal_whitoutquotes(str) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		if (!(str[i] == '"' || str[i] == '\''))
		{
			ptr[j] = str[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (free(str), ptr);
}
