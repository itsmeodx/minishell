/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:49:06 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:05 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_and(t_tree *tree)
{
	int	status;

	status = ft_execution(tree->left);
	if (status == EXIT_SUCCESS)
		return (ft_execution(tree->right));
	return (status);
}

int	execute_or(t_tree *tree)
{
	int	status;

	status = ft_execution(tree->left);
	if (status != EXIT_SUCCESS && status != 130)
		return (ft_execution(tree->right));
	return (status);
}
