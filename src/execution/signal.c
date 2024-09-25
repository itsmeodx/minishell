/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:09:51 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/25 10:01:21 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

bool	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	return (true);
}

void	ft_sigheredoc(int sig)
{
	if (sig == SIGINT)
		ft_exit(130);
}

void	ft_signal(int sig)
{
	char	*prompt;

	if (sig == SIGINT)
	{
		g_data.exit_status = 128 + sig;
		prompt = create_full_prompt();
		rl_replace_line("", 0);
		ft_printf("\n%s", prompt);
		free(prompt);
	}
	return ;
}
