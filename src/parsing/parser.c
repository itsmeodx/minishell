/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:43:23 by adam              #+#    #+#             */
/*   Updated: 2024/08/12 18:52:31 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_set_type(t_link **node, char *input)
{
	if (*node == NULL)
		return ;
	if (!ft_strncmp(input, "<", ft_strlen(input)))
		(*node)->identifer = IN;
	else if (!ft_strncmp(input, ">", ft_strlen(input)))
		(*node)->identifer = OUT;
	else if (!ft_strncmp(input, "<<", ft_strlen(input)))
		(*node)->identifer = HERDOC;
	else if (!ft_strncmp(input, ">>", ft_strlen(input)))
		(*node)->identifer = APPEND;
	else if (!ft_strncmp(input, "|", ft_strlen(input)))
		(*node)->identifer = PIPE;
	else if (!ft_strncmp(input, "||", ft_strlen(input)))
		(*node)->identifer = OR;
	else if (!ft_strncmp(input, "&&", ft_strlen(input)))
		(*node)->identifer = AND;
	else if (!ft_strncmp(input, "(", ft_strlen(input)))
		(*node)->identifer = OPEN_PAR;
	else if (!ft_strncmp(input, ")", ft_strlen(input)))
		(*node)->identifer = CLOSE_PAR;
	else
		(*node)->identifer = STR;
}

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
		ft_set_type(&node, input[i]);
		ft_dbl_lstadd_back(&link, node);
		i++;
	}
	return (link);
}

void	ft_parsing(char *input)
{
	t_link	*link;
	char	**split_input;
	t_link *tmp;
	t_link *target;

	target = NULL;
	split_input = ft_lexer(input);
	link = ft_def_type(split_input);
	tmp = link;
	target = ft_find_hightest_proirity(tmp);
	if (tmp)
		printf("target: %s\n", target->command);
	else 
		printf("null\n");
	// ft_create_tree(link);
	// t_link *tmp = link;
	// while(tmp)
	// {
	//     printf("command: %s\n", tmp->command);
	//     printf("type: %d\n", tmp->identifer);
	//     tmp = tmp->next;
	// }
	ft_dbl_lstclear(&link);
}
