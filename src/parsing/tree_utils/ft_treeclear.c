/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:12:27 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/25 13:33:36 by akhobba          ###   ########.fr       */
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
}

void	ft_treeclear(t_tree *tree)
{
	if (!tree)
		return ;
	ft_treeclear_node(tree);
	ft_treeclear(tree->left);
	ft_treeclear(tree->right);
	free(tree);
}
