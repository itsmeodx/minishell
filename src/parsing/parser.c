/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:43:23 by adam              #+#    #+#             */
/*   Updated: 2024/08/05 16:14:44 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void	ft_set_type(t_link **node, char *input)
{
		if (!ft_strncmp(input, "<", ft_strlen(input)))
			(*node)->identifer = LESS;
		else if (!ft_strncmp(input, ">", ft_strlen(input)))
			(*node)->identifer = GREAT;
		else if (!ft_strncmp(input, "<<", ft_strlen(input)))
			(*node)->identifer = LESSLESS;
		else if (!ft_strncmp(input, ">>", ft_strlen(input)))
			(*node)->identifer = GREATGREAT;
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
	while (input)
	{
		node = ft_dbl_lstnew(input[i]);
		ft_set_type(&node, input[i]);
		printf("here\n");
		ft_dbl_lstadd_back(&link, node);
		i++;
	}
	return (link);
}


void ft_parsing(char *input)
{
	t_link		*link;
	char		**split_input;

	split_input = ft_lexer(input);
	printf("lexer clean\n");
	link = ft_def_type(split_input);
    t_link *tmp = link;
    while(tmp)
    {
        printf("command: %s\n", tmp->command);
        printf("type: %d\n", tmp->identifer);
        tmp = tmp->next;
    }
}