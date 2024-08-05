/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:20:04 by adam              #+#    #+#             */
/*   Updated: 2024/08/05 15:43:33 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_error	*g_error;

int	main(void)
{
	char			*input;

	// g_error = NULL;
	while (1)
	{
		input = readline("minishell>");
		if (input)
			add_history(input);
        // temporary exit condition
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
        ft_parsing(input);
        // ft_lexer(input);
	}
	return (0);
}