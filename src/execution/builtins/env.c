/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:04:14 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/11 12:04:14 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	builtin_env(t_cmd *cmd __attribute__((unused)))
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = fork();
	if (pid == -1)
		return (g_data.exit_status = EXIT_FAILURE, false);
	if (pid == 0)
	{
		g_data.environ = filter_env(g_data.environ);
		while (g_data.environ && g_data.environ[++i])
			printf("%s\n", g_data.environ[i]);
		ft_exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	return (g_data.exit_status = EXIT_SUCCESS, true);
}
