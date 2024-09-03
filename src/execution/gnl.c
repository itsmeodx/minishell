/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:08:03 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/03 13:08:28 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

//char	*get_next_line(int fd)
//{
//	char	*str;
//	char	*buff;
//
//	str = malloc(1000000);
//	if (!str)
//		return (NULL);
//	buff = str;
//	while (fd != -1 && read(fd, buff, 0) != -1 && read(fd, buff, 1)
//		&& *buff++ != '\n');
//	if (buff > str)
//		return (*buff = 0, str);
//	else
//		return (free(str), NULL);
//}

char	*get_next_line(int fd)
{
	int		len;
	char	*buff;
	char	*str;

	len = 1;
	buff = malloc(sizeof(char ) * (len + 1));
	if (!buff || read(fd, buff, 0) == -1)
		return (free(buff), NULL);
	while (read(fd, buff + len - 1, 1) && buff[len++ - 1] != '\n')
	{
		str = buff;
		buff = malloc(sizeof(char ) * (len + 1));
		if (!buff)
			return (free(str), NULL);
		strncpy(buff, str, len - 1);
		free(str);
	}
	if (len == 1)
		return (free(buff), NULL);
	buff[len - 1] = 0;
	return (buff);
}
