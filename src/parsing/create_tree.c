/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:41 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/12 07:35:03 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

t_tree *ft_create_tree(t_tree **tree, t_link *link)
{
    t_tree *node;
    t_link *tmp;

    *tree = NULL;
    while (tmp)
    {
        node = ft_treenew(tmp->command, tmp->identifer);
        if (!*tree)
            ft_treeadd_back_right(&tree, node);
        if(*tree)
        {
            if ((*tree)->type < node->type)
            {
                ft_treeadd_back_left(&tree, node);
                *tree = (*tree)->left;
            }
            else
            {
                ft_treeadd_back_right(&tree, node);
                *tree = (*tree)->right;
            }
        }
        ft_free_tree(&node);
        tmp = tmp->next;
    }
    return (*tree);
}
