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

	colored = ft_strjoin(color, str);
	reset = ft_strjoin(colored, RESET);
	free(colored);
	return (reset);
}

char	*ft_getprompt(void)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;

	prompt = NULL;
	cwd = getcwd(NULL, 0);
	tmp = cwd;
	cwd = ft_strjoin(cwd, " ");
	free(tmp);
	if (getenv("HOME") && strncmp(cwd, getenv("HOME"), strlen(getenv("HOME"))) == 0)
		prompt = ft_strjoin("~", cwd + strlen(getenv("HOME")));
	tmp = prompt;
	prompt = colorize(prompt, GREEN);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(PROMPT, prompt);
	free(tmp);
	free(cwd);
	return (prompt);
}
