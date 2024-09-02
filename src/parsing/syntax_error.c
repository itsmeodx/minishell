/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:27:21 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/01 10:33:57 akhobba          ###   ########.fr       */
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

	// TODO: ls () --> handle this case
	// TODO: check
	error = ft_check_redirection(link);
	if (error)
	{
		ft_printf_error(error);
		return (true);
	}
	error = ft_check_parentheses(link);
	if (error)
	{
		ft_printf_error(error);
		return (true);
	}
	error = ft_check_quotes(link);
	if (error)
	{
		ft_printf_error(error);
		return (true);
	}
	error = ft_check_and_or(link);
	if (error)
	{
		ft_printf_error(error);
		return (true);
	}
	return (false);
}

void	ft_onemsg(char *error)
{
	dprintf(STDERR_FILENO, "%sminishell%s: syntax error near unexpected token `%s'\n",
		RED, RESET, error);
	g_data.exit_status = 2;
}

void	ft_printf_error(t_errorn error)
{
	if (error == ERROR_IN)
		ft_onemsg("newline");
	else if (error == ERROR_OUT)
		ft_onemsg("newline");
	else if (error == ERROR_APPEND)
		ft_onemsg(">>");
	else if (error == ERROR_AND)
		ft_onemsg("&&");
	else if (error == ERROR_OR)
		ft_onemsg("||");
	else if (error == ERROR_SIGNAL_QUOTE)
		ft_onemsg("'");
	else if (error == ERROR_DOUBLE_QUOTE)
		ft_onemsg("\"");
	else if (error == ERROR_OPEN_PAREN)
		ft_onemsg("(");
	else if (error == ERROR_CLOSE_PAREN)
		ft_onemsg(")");
	else if (error == ERROR_HERDOC)
		ft_onemsg("<<");
	else if (error == ERROR_PIPE)
		ft_onemsg("|");
}
