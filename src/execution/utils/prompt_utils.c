/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:18:20 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/05 15:18:20 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*getpwd(void)
{
	char	*str[2];

	str[0] = getcwd(NULL, 0);
	str[1] = ft_strjoin(str[0], " ");
	free(str[0]);
	if (ft_getenv("HOME")
		&& strncmp(str[1], ft_getenv("HOME"), strlen(ft_getenv("HOME"))) == 0)
		str[0] = ft_strjoin("~", str[1] + strlen(ft_getenv("HOME")));
	else
		str[0] = ft_strdup(str[1]);
	free(str[1]);
	str[1] = colorize(str[0], YELLOW);
	free(str[0]);
	str[0] = ft_strjoin(" ", str[1]);
	free(str[1]);
	return (str[0]);
}

int	get_term_width(void)
{
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

char	*get_exit_status(void)
{
	char	*str[2];

	if (g_data.exit_status != 0)
		str[0] = ft_itoa(g_data.exit_status);
	else
		str[0] = ft_strdup("✔");
	if (g_data.exit_status != 0)
		str[1] = colorize(str[0], RED);
	else
		str[1] = colorize(str[0], GREEN);
	free(str[0]);
	str[0] = ft_strjoin(str[1], RESET);
	free(str[1]);
	str[1] = ft_strjoin(" ", str[0]);
	free(str[0]);
	return (str[1]);
}
