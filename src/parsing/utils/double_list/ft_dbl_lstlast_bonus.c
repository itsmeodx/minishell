/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_lstlast_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:52:32 by adam              #+#    #+#             */
/*   Updated: 2024/08/11 20:45:58 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h" 

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