/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/27 12:42:19 by adam             ###   ########.fr       */
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
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		tree = ft_parsing(input);
		free(input);
	}
	ft_treeclear(tree);
	return (0);
}
