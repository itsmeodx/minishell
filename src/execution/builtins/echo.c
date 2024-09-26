/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/26 18:11:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	parse_n_flag(t_cmd *cmd, int *n_flag)
{
	int	i;
	int	j;

	i = 1;
	*n_flag = 0;
	while (i < cmd->argc && cmd->argv[i][0] == '-')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] == 0)
		{
			*n_flag = 1;
			i++;
		}
		else
			break ;
	}
	return (i);
}

void	print_arguments(t_cmd *cmd, int i, int n_flag)
{
	while (i < cmd->argc)
	{
		ft_printf("%s", cmd->argv[i]);
		if (i + 1 < cmd->argc)
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
}

bool	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = parse_n_flag(cmd, &n_flag);
	print_arguments(cmd, i, n_flag);
	return (g_data()->exit_status = EXIT_SUCCESS, true);
}
