/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:13:33 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 15:56:41 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	ft_execution(t_tree *tree)
{
	if (tree->type == STR)
		return (execute_str(tree));
	else if (tree->type == PIPE)
		return (execute_pipe(tree));
	else if (tree->type == AND)
		return (execute_and(tree));
	else if (tree->type == OR)
		return (execute_or(tree));
	else if (tree->type == OPEN_PAR)
		return (execute_par(tree));
	return (EXIT_FAILURE);
}
