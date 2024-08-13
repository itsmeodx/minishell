/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:20:04 by adam              #+#    #+#             */
/*   Updated: 2024/08/13 10:29:22 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

int	main(void)
{
	char	*input;

	// g_error = NULL;
	while (1)
	{
		input = readline("parsing>");
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
