/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:26:16 by akhobba           #+#    #+#             */
/*   Updated: 2024/08/12 18:59:33 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

t_link  *ft_search_target(t_link *head, int target)
{ 
    t_link *tmp;

    tmp = head;
    while (tmp)
    {
        if(tmp->identifer == OPEN_PAR)
        {
            while (tmp->identifer != CLOSE_PAR)
            {
                tmp = tmp->next;
                if (!tmp)
                    return (NULL);
            }
        }
        if (tmp->identifer == target)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}

int *ft_fill_priority(void)
{
    int *priority;
    int i;
    int j;

    priority = malloc(4 * 10);
    memset(priority, 0, sizeof(int));
    if (!priority)
        return (NULL);
    i = 0;
    j = 9;
    while (i < 10)
    {
        priority[i] = j;
        i++;
        j--;
    }
    return (priority);
}

t_link  *ft_find_hightest_proirity(t_link *head)
{
    t_link *target;
    int    *priority;
    int     i;

    i = 0;
    target = NULL;
    priority = ft_fill_priority();
    while (i < 10)
    {
        target = ft_search_target(head, priority[i]);
        if (target)
        {
            printf("target 1 %s\n", target->command);
            return (free(priority),target);
        }
        i++;
    }
    return (free(priority),target);
}
