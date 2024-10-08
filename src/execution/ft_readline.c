/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:13:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/26 18:11:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_readline(char *prompt)
{
	char	*line;

	line = readline(prompt);
	free(prompt);
	if (line && *line)
		ft_add_history(line);
	free(g_data()->input);
	return (line);
}
