/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:13:33 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/05 12:25:15 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	ft_execution(t_tree *tree)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (tree->type == STR)
		ret = execute_str(tree);
	else if (tree->type == PIPE)
		ret = execute_pipe(tree);
	else if (tree->type == AND)
		ret = execute_and(tree);
	else if (tree->type == OR)
		ret = execute_or(tree);
	else if (tree->type == OPEN_PAR)
		ret = execute_par(tree);
	if (g_data()->exit_status == SIGINT + 128)
		ft_printf("\n");
	else if (g_data()->exit_status == SIGQUIT + 128)
		ft_printf("Quit (core dumped)\n");
	return (ret);
}
