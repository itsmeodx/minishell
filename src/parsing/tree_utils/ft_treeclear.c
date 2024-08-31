/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:12:27 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/31 15:27:00 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_treeclear_node(t_tree *tree)
{
	if (!tree)
		return ;
	free_2d(tree->cmd->argv);
	free(tree->cmd);
	if (tree->redirection)
		ft_lstclear_redi(&tree->redirection);
	free(tree);
}

void	ft_treeclear(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		ft_treeclear(tree->left);
	if (tree->right)
		ft_treeclear(tree->right);
	ft_treeclear_node(tree);
}
