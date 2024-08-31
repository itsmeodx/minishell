/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/31 17:11:55 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	main(void)
{
	char	*input;
	t_tree	*tree;

	tree = NULL;
	while (1)
	{
		input = readline("minishell>");
		if (input)
			add_history(input);
		if (!input)
			return (1);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		tree = ft_parsing(input);
		free(input);
		ft_treeclear(tree);
	}
	if (!tree)
		ft_treeclear(tree);
	return (0);
}
