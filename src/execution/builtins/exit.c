/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:58:08 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/24 21:32:02 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	ft_exit(int status)
{
	ft_treeclear(g_data.tree);
	free_2d(g_data.environ);
	rl_clear_history();
	close(g_data.hfd);
	free(g_data.home);
	free(g_data.input);
	free(g_data.last_line);
	ft_garbage_clear(&g_data.garbage);
	exit(status);
}

static
bool	check_status(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (isdigit(str[i]))
		i++;
	while (str[i] >= 9 & str[i] <= 13 || str[i] == 32)
		i++;
	if (str[i])
		return (false);
	return (true);
}

bool	builtin_exit(t_cmd *cmd)
{
	unsigned char	status;

	status = 0;
	if (cmd->argc == 1)
		ft_exit(g_data.exit_status);
	if (!check_status(cmd->argv[1]))
		return (ft_dprintf(STDERR_FILENO, "exit\n"), ft_dprintf(STDERR_FILENO,
				NAME"exit: %s: "NAR"\n", cmd->argv[1]), ft_exit(2), false);
	else if (cmd->argc > 2)
		return (ft_dprintf(STDERR_FILENO, "exit\n"), ft_dprintf(STDERR_FILENO,
				NAME"exit: "TMA"\n"), g_data.exit_status = 1, false);
	status = ft_atoi(cmd->argv[1]);
	ft_printf("exit\n");
	ft_exit(status);
	return (true);
}
