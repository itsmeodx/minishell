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

static
char	*get_user_host(void)
{
	char	*str[3];

	str[2] = ft_strdup(ft_getenv("USER"));
	if (!str[2])
		str[2] = get_output((char *[]){"/usr/bin/whoami", NULL});
	if (!str[2])
		str[2] = ft_strdup("user");
	str[0] = ft_strjoin(CYAN, str[2]);
	str[1] = ft_strjoin(str[0], "@");
	free(str[0]);
	str[0] = ft_strjoin(str[1], ft_getenv("MINI_HOSTNAME"));
	free(str[1]);
	str[1] = ft_strjoin(str[0], RESET);
	free(str[0]);
	str[0] = ft_strjoin(str[1], "> ");
	return (free(str[1]), free(str[2]), str[0]);
}

char	*ft_getprompt(void)
{
	char	*str[4];

	str[0] = get_user_host();
	str[1] = getpwd();
	str[2] = ft_strjoin(str[0], str[1]);
	free(str[0]);
	free(str[1]);
	str[0] = ft_strjoin("\n╭──<", str[2]);
	free(str[2]);
	str[3] = get_branch();
	str[2] = ft_strjoin(str[0], str[3]);
	return (free(str[3]), free(str[0]), str[2]);
}

char	*create_full_prompt(void)
{
	char	*str[5];
	int		len[4];

	str[0] = ft_getprompt();
	str[2] = get_exit_status();
	len[0] = ft_strlen(str[0]) - (ft_strlen(CYAN RESET YELLOW RESET)
			+ (ft_strlen(CYAN RESET) * (g_data.branch == true)) + 1 + (2 * 4));
	len[1] = ft_strlen(str[2]) - ((ft_strlen(RED RESET) + 6)
			* (g_data.exit_status != 0) + (ft_strlen(GREEN RESET) + 8)
			* (g_data.exit_status == 0));
	len[3] = get_term_width();
	len[2] = len[3] - (len[0] + len[1]);
	if (len[2] < 0)
		len[2] = 0;
	str[1] = ft_itoa(len[2]);
	str[4] = ft_strjoin("\033[", str[1]);
	free(str[1]);
	str[1] = ft_strjoin(str[4], "C");
	str[3] = ft_strjoin(str[0], str[1]);
	free(str[0]);
	free(str[1]);
	str[0] = ft_strjoin(str[3], str[2]);
	str[1] = ft_strjoin(str[0], "\n\001╰───\002>\r\033[6C");
	return (free(str[0]), free(str[2]), free(str[3]), free(str[4]), str[1]);
}
