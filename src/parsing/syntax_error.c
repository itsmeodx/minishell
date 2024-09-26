/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:27:21 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/26 18:11:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_errorn	ft_check_redirection(t_link *link)
{
	t_errorn	error;

	error = ft_check_pipe(link);
	if (error)
		return (error);
	error = ft_check_in(link);
	if (error)
		return (error);
	error = ft_check_out(link);
	if (error)
		return (error);
	error = ft_check_append(link);
	if (error)
		return (error);
	error = ft_check_herdoc(link);
	if (error)
		return (error);
	return (NONE);
}

int	ft_syntax_error(t_link *link)
{
	t_errorn	error;

	error = ft_check_and_or(link);
	if (error)
		return (ft_printf_error(error), true);
	error = ft_check_redirection(link);
	if (error)
		return (ft_printf_error(error), true);
	error = ft_check_parentheses(link);
	if (error)
		return (ft_printf_error(error), true);
	error = ft_check_quotes(link);
	if (error)
		return (ft_printf_error(error), true);
	return (false);
}

void	ft_onemsg(char *error, t_errorn errorn)
{
	if (errorn == ERROR_NUM_HERDOC)
		ft_dprintf(STDERR_FILENO,
			NAME"%s\n", error);
	else
		ft_dprintf(STDERR_FILENO,
			NAME"syntax error near unexpected token `%s'\n", error);
	g_data()->exit_status = 2;
}

void	ft_printf_error(t_errorn error)
{
	int				i;
	static t_errorn	errorn[] = {ERROR_IN, ERROR_OUT, ERROR_APPEND, ERROR_AND,
		ERROR_OR, ERROR_SIGNAL_QUOTE, ERROR_DOUBLE_QUOTE, ERROR_OPEN_PAREN,
		ERROR_CLOSE_PAREN, ERROR_HERDOC, ERROR_PIPE, ERROR_NUM_HERDOC};
	static char		*error_msg[] = {"newline", "newline", ">>", "&&", "||",
		"'", "\"", "(", ")", "<<", "|", "maximum here-document count exceeded"};

	i = -1;
	while (errorn[++i])
	{
		if (error == errorn[i])
		{
			ft_onemsg(error_msg[i], error);
			break ;
		}
	}
}
