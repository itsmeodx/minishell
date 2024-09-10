/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:13:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/10 18:07:52 by akhobba          ###   ########.fr       */
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
	free(g_data.input);
	return (line);
}
