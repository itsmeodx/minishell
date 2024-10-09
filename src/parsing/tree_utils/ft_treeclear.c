/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:12:27 by akhobba           #+#    #+#             */
/*   Updated: 2024/10/05 12:39:16 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_treeclear_node(t_tree *tree)
{
	if (!tree)
		return ;
	free_2d(tree->cmd->argv);
	free(tree->cmd);
	if (tree->redirections)
		ft_lstclear_redi(&tree->redirections);
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

void	ft_treesclear(t_tree **trees)
{
	int	i;

	i = 0;
	while (trees && trees[i])
	{
		ft_treeclear(trees[i]);
		i++;
	}
	free(trees);
}

// void	ft_treeclear(t_tree *tree)
// {
// 	t_tree	*tmp_left;
// 	t_tree	*tmp_right;

// 	if (!tree)
// 		return ;
// 	tmp_left = tree->left;
// 	tmp_right = tree->right;
// 	ft_treeclear_node(tree);
// 	ft_treeclear(tmp_left);
// 	ft_treeclear(tmp_right);
// }
