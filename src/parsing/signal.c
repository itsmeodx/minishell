/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:09:51 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/10 19:02:44 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

void	ft_signal(int sig)
{
	char	*prompt;

	if (sig == SIGINT)
	{
		prompt = create_full_prompt();
		g_data.exit_status = 128 + sig;
		rl_replace_line("", 0);
		printf("\n%s", prompt);
		free(prompt);
	}
	return ;
}
