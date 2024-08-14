/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:25:15 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/14 10:34:25 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_tree(t_tree *node)
{
	free_2d(node->cmd->argv);
	free(node->cmd);
	free(node);
}

t_cmd	*ft_cmdnew(char *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->argv = (char **)malloc(sizeof(char *) *  1);
	new->argv[0] = ft_strdup(cmd);
	new->argc = 1;
	return (new);
}

t_tree	*ft_treenew(char *cmd, int type)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = type;
	tree->cmd = ft_cmdnew(cmd);
	tree->exit_status = -1;
	tree->prev = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

void	ft_treeadd_back_right(t_tree **tree, t_tree *new)
{
	t_tree	*tmp;

	if (!(*tree))
		return ;
	if (!(*tree))
	{
		*tree = new;
		return ;
	}
	tmp = *tree;
	tmp->right = new;
	new->prev = tmp;
}

void	ft_treeadd_back_left(t_tree **tree, t_tree *new)
{
	t_tree	*tmp;

	if (!tree)
		return ;
	if (!(*tree))
	{
		*tree = new;
		return ;
	}
	tmp = *tree;
	tmp->left = new;
	new->prev = tmp;
}
