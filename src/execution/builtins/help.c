/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:25 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/03 19:20:37 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// display the help message of the shell.
bool	builtin_help(t_cmd *cmd __attribute__((unused)))
{
	ft_printf("Welcome to 42minishell!\n");
	ft_printf("Available built-in commands:\n");
	ft_printf("  cd\t\t[dir/-]\t\t- Change directory to [dir] or previous (-).\n");
	ft_printf("  echo\t\t[-n][str]\t- Display [str] with optional newline.\n");
	ft_printf("  env\t\t\t\t- List environment variables.\n");
	ft_printf("  exit\t\t[status]\t- Exit shell with [status].\n");
	ft_printf("  export\t[var=val]\t- Set environment variable.\n");
	ft_printf("  help\t\t\t\t- Display this help message.\n");
	ft_printf("  alias\t\t[name=val]\t- Set command alias.\n");
	ft_printf("  unalias\t[-a][n]\t\t- Remove alias.\n");
	ft_printf("  pwd\t\t\t\t- Print working directory.\n");
	ft_printf("  unset\t\t[var]\t\t- Unset environment variable.\n");
	ft_printf("\nSupports piping, redirection, and subshells:\n");
	ft_printf("  cmd | cmd\t\t\t- Pipe output of first cmd to second.\n");
	ft_printf("  cmd > file\t\t\t- Redirect output to file.\n");
	ft_printf("  cmd >> file\t\t\t- Append output to file.\n");
	ft_printf("  cmd < file\t\t\t- Use file as input.\n");
	ft_printf("  cmd << delim\t\t\t- Read input until delim.\n");
	ft_printf("  cmd && cmd\t\t\t- Run second cmd if first succeeds.\n");
	ft_printf("  cmd || cmd\t\t\t- Run second cmd if first fails.\n");
	ft_printf("  $var\t\t\t\t- Substitute variable value.\n");
	ft_printf("  (cmd)\t\t\t\t- Run cmd in subshell.\n");
	ft_printf("\nCtrl+C to terminate, Ctrl+D to exit.\n");
	return (g_data()->exit_status = EXIT_SUCCESS, true);
}
