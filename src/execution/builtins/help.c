/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:47:25 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/03 18:39:02 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// display the help message of the shell.
bool	builtin_help(t_cmd *cmd __attribute__((unused)))
{
	ft_printf("Welcome to 42minishell!\n");
	ft_printf("Here are the available built-in commands:\n");
	ft_printf("  cd [directory/-]         "
		"- Change the current directory to [directory].\n");
	ft_printf("                             "
		"If no directory is specified, it changes to the home directory.\n");
	ft_printf("                             "
		"If the directory is '-', it changes to the previous directory.\n");
	ft_printf("  echo [-n][string]        "
		"- Display [string] to the terminal.\n");
	ft_printf("                             "
		"Supports escape sequences like \\n for new line.\n");
	ft_printf("  env                      "
		"- Display the environment variables.\n");
	ft_printf("                             "
		"Lists all the environment variables currently set.\n");
	ft_printf("  exit [status]            "
		"- Exit the shell with a status of [status].\n");
	ft_printf("                             "
		"If no status is provided, it exits with the status of "
		"the last executed command.\n");
	ft_printf("  export [variable=value]  "
		"- Set the environment variable [variable].\n");
	ft_printf("                             "
		"Adds the specified variable to the environment.\n");
	ft_printf("  help                     "
		"- Display this help message.\n");
	ft_printf("                             "
		"Provides information about built-in commands.\n");
	ft_printf("  alias [name=value]       "
		"- Set an alias for a command.\n");
	ft_printf("                             "
		"Creates a shortcut for a command with the specified name.\n");
	ft_printf("  unalias [-a][name]       "
		"- Remove an alias.\n");
	ft_printf("                             "
		"Deletes the specified alias from the list of aliases.\n");
	ft_printf("  pwd                      "
		"- Print the current working directory.\n");
	ft_printf("                             "
		"Displays the full pathname of the current directory.\n");
	ft_printf("  unset [variable]         "
		"- Unset the environment variable [variable].\n");
	ft_printf("                             "
		"Removes the specified variable from the environment.\n");
	ft_printf("\nUse the man command for information on other programs.\n");
	ft_printf("Minishell also supports piping, redirection, "
		"and background execution.\n");
	ft_printf("  [command] | [command]    "
		"- Pipe the output of the first command to the input of "
		"the second command.\n");
	ft_printf("  [command] > [file]       "
		"- Redirect the output of the command to the specified file.\n");
	ft_printf("  [command] >> [file]      "
		"- Append the output of the command to the specified file.\n");
	ft_printf("  [command] < [file]       "
		"- Use the specified file as input to the command.\n");
	ft_printf("  [command] << [delimiter] "
		"- Read input from the terminal until the specified "
		"delimiter is encountered.\n");
	ft_printf("  [command] && [command]   "
		"- Execute the second command only if the first command "
		"is successful.\n");
	ft_printf("  [command] || [command]   "
		"- Execute the second command only if the first command fails.\n");
	ft_printf("  [$variable]              "
		"- Substitute the value of the variable in the command.\n");
	ft_printf("  ([command])              "
		"- Execute the command in a subshell.\n");
	ft_printf("\nUse Ctrl+C to terminate the current command.\n");
	ft_printf("Use Ctrl+D to exit the shell.\n");
	return (g_data()->exit_status = EXIT_SUCCESS, true);
}
