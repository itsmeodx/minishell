/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/12 16:59:59 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	builtin_pwd(t_cmd *cmd __attribute__((unused)))
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(ft_getenv("PWD"));
	if (!cwd)
		return (dprintf(STDERR_FILENO,
				NAME"pwd: error retrieving current directory: "),
			dprintf(STDERR_FILENO,
				"getcwd: cannot access parent directories: "NSFOD"\n"),
			g_data.exit_status = EXIT_FAILURE, false);
	printf("%s\n", cwd);
	return (free(cwd), g_data.exit_status = EXIT_SUCCESS, true);
}
