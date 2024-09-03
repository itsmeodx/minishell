/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:57:59 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 19:57:59 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*colorize(char *str, char *color)
{
	char	*colored;
	char	*reset;

	if (!str)
		return (NULL);
	colored = ft_strjoin(color, str);
	reset = ft_strjoin(colored, RESET);
	free(colored);
	return (reset);
}

char	*get_user_host(void)
{
	char	*str[2];

	str[0] = ft_strjoin(CYAN, ft_getenv("USER"));
	str[1] = ft_strjoin(str[0], "@");
	free(str[0]);
	str[0] = ft_strjoin(str[1], ft_getenv("HOSTNAME"));
	free(str[1]);
	str[1] = ft_strjoin(str[0], RESET);
	free(str[0]);
	str[0] = ft_strjoin(str[1], ":> ");
	free(str[1]);
	return (str[0]);
}

char	*ft_getprompt(void)
{
	char	*str[4];

	str[0] = NULL;
	str[3] = get_user_host();
	str[2] = getcwd(NULL, 0);
	str[1] = str[2];
	str[2] = ft_strjoin(str[2], " ");
	free(str[1]);
	if (ft_getenv("HOME")
		&& strncmp(str[2], ft_getenv("HOME"), strlen(ft_getenv("HOME"))) == 0)
		str[0] = ft_strjoin("~", str[2] + strlen(ft_getenv("HOME")));
	else
		str[0] = ft_strdup(str[2]);
	free(str[2]);
	str[1] = str[0];
	str[0] = ft_strjoin(YELLOW, str[0]);
	free(str[1]);
	str[1] = str[0];
	str[0] = ft_strjoin(str[0], RESET);
	free(str[1]);
	str[1] = str[0];
	str[0] = ft_strjoin(str[3], str[0]);
	free(str[1]);
	free(str[3]);
	return (str[0]);
}
