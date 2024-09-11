/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:49:06 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 15:57:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_and(t_tree *tree)
{
	if (ft_execution(tree->left) == EXIT_SUCCESS)
		return (ft_execution(tree->right));
	return (EXIT_FAILURE);
}

int	execute_or(t_tree *tree)
{
	if (ft_execution(tree->left) != EXIT_SUCCESS)
		return (ft_execution(tree->right));
	return (EXIT_SUCCESS);
}
