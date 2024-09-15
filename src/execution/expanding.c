/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:59:07 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/12 18:04:44 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*ft_expanding(char *str)
{
	int		i[3];
	char	*tmp[3];

	i[0] = -1;
	while (str && str[++i[0]])
	{
		if (str[i[0]] == '\'' || str[i[0]] == '\"')
		{
			i[1] = i[0] + get_next_quote(str + i[0] + 1, str[i[0]]);
			tmp[0] = ft_substr(str, 0, i[0]);
			tmp[2] = ft_substr(str, i[0] + 1, i[1] - i[0]);
			if (str[i[0]] == '\"')
				tmp[2] = expand_dollar(tmp[2]);
			i[2] = ft_strlen(tmp[2]);
			tmp[1] = ft_strjoin(tmp[0], tmp[2]);
			free(tmp[0]);
			free(tmp[2]);
			tmp[0] = ft_strjoin(tmp[1], str + i[1] + 2);
			free(tmp[1]);
			free(str);
			str = tmp[0];
			i[0] += i[2] - 1;
		}
	}
	return (str);
}
