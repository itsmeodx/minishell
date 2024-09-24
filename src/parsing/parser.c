/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:57:26 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/24 21:37:03 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_set_type(t_link **node, char *input)
{
	if (*node == NULL)
		return ;
	if (!ft_strncmp(input, "<", ft_strlen(input)))
		(*node)->identifier = IN;
	else if (!ft_strncmp(input, ">", ft_strlen(input)))
		(*node)->identifier = OUT;
	else if (!ft_strncmp(input, "<<", ft_strlen(input)))
		(*node)->identifier = HEREDOC;
	else if (!ft_strncmp(input, ">>", ft_strlen(input)))
		(*node)->identifier = APPEND;
	else if (!ft_strncmp(input, "|", ft_strlen(input)))
		(*node)->identifier = PIPE;
	else if (!ft_strncmp(input, "||", ft_strlen(input)))
		(*node)->identifier = OR;
	else if (!ft_strncmp(input, "&&", ft_strlen(input)))
		(*node)->identifier = AND;
	else if (!ft_strncmp(input, "(", ft_strlen(input)))
		(*node)->identifier = OPEN_PAR;
	else if (!ft_strncmp(input, ")", ft_strlen(input)))
		(*node)->identifier = CLOSE_PAR;
	else
		(*node)->identifier = STR;
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

bool	ft_is_redirection(int identifier)
{
	if (identifier == IN || identifier == OUT || identifier == APPEND
		|| identifier == HEREDOC)
		return (true);
	return (false);
}

t_tree	*ft_parsing(char *input)
{
	t_link	*link;
	char	**split_input;
	t_link	*tmp;
	t_tree	*tree;

	tree = NULL;
	g_data.garbage = NULL;
	split_input = ft_lexer(input);
	link = ft_def_type(split_input);
	tmp = link;
	free_2d(split_input);
	ft_open_herdoc(&tmp, 0, 0);
	if (ft_syntax_error(tmp))
	{
		ft_garbage_clear(&g_data.garbage);
		return (free_2d(split_input), NULL);
	}
	tree = ft_parse_and_or(tmp);
	ft_generate_spaces(10);
	ft_printf_tree(tree, 0, 2);
	printf("\n");
	ft_garbage_clear(&g_data.garbage);
	return (tree);
}

	// ft_printf_link(link);
	// ft_dbl_lstclear(&link);
