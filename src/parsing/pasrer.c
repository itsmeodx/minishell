/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasrer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:43:23 by adam              #+#    #+#             */
/*   Updated: 2024/08/05 00:55:21 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

t_link	*ft_def_type(char **input)
{
	t_link	*link;
	t_link	*node;
	int		i;

	i = 0;
	link = NULL;
	while (input[i])
	{
		node = ft_dbl_lstnew(input[i]);
		if (!ft_strncmp(input[i], "<", ft_strlen(input[i])))
			node->identifer = LESS;
		else if (!ft_strncmp(input[i], ">", ft_strlen(input[i])))
			node->identifer = GREAT;
		else if (!ft_strncmp(input[i], "<<", ft_strlen(input[i])))
			node->identifer = LESSLESS;
		else if (!ft_strncmp(input[i], ">>", ft_strlen(input[i])))
			node->identifer = GREATGREAT;
		else if (!ft_strncmp(input[i], "|", ft_strlen(input[i])))
			node->identifer = PIPE;
		else
			node->identifer = STR;
		ft_dbl_lstadd_back(&link, node);
		i++;
	}
	return (link);
}


void ft_parsing(char **input)
{
	t_link		*link;
	char		**split_input;

    link = NULL;
	split_input = ft_lexer(input);
    printf("split_input: %s\n", split_input[0]);
	link = ft_def_type(split_input);
    t_link *tmp = link;
    while(tmp)
    {
        printf("command: %s\n", tmp->command);
        printf("type: %d\n", tmp->identifer);
        tmp = tmp->next;
    }
}