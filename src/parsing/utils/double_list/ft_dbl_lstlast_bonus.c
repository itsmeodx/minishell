/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_lstlast_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:52:32 by adam              #+#    #+#             */
/*   Updated: 2024/08/05 00:53:04 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h" 

t_link	*ft_dbl_lstlast(t_link *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}