/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/04 15:59:07 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

/*
** global variable
*/
struct s_data	*g_data(void)
{
	static t_data	data;

	return (&data);
}

void	*ft_semicolon(char *input)
{
	char	**split_input;
	int		len;
	void	**ptr;	
	int		i;

	i = 0;
	split_input = ft_qsplit(input, ";");
	///
	while (split_input[i])
		printf("%s\n", split_input[i++]);
	///
	i = 0;
	len = ft_strlen_2d(split_input);
	ptr = malloc(sizeof(t_tree) * (len + 1)); 
	if (!ptr)
		return (NULL);
	while(split_input[i])
	{
	 	ptr[i] = ft_parsing(split_input[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env)
{
	// void	**ptr;

	init_minishell(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (true)
	{
		signal(SIGINT, ft_signal);
		g_data()->input = ft_readline(create_full_prompt());
		if (!g_data()->input)
			break ;
		// g_data()->tree = ft_parsing(g_data()->input);
		// ptr = ft_semicolon(g_data()->input);		
		// int i = 0;
		// while (ptr[i])
		// {
		// 	ft_generate_spaces(10);
		// 	ft_printf_tree((t_tree *)ptr[i], 0, 2);
		// 	printf("\n");
		// 	i++;	
		// }
		break; // do what you schould do
		if (!g_data()->tree)
			continue ;
		ft_execution(g_data()->tree);
		ft_treeclear(g_data()->tree);
		g_data()->tree = NULL;
		if (g_data()->exit_status == SIGINT + 128)
			ft_printf("\n");
		else if (g_data()->exit_status == SIGQUIT + 128)
			ft_printf("Quit (core dumped)\n");
	}
	ft_printf("exit\n");
	ft_exit(g_data()->exit_status);
}
