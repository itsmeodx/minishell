/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:18:20 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/18 09:37:18 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*getpwd(void)
{
	char	*str[2];

	str[0] = ft_strdup(ft_getenv("PWD"));
	if (!str[0])
		str[0] = getcwd(NULL, 0);
	if (!str[0])
		str[0] = ft_strdup(ft_getenv("PWD"));
	if (!str[0])
		str[0] = ft_strdup("");
	if (ft_getenv("HOME")
		&& strncmp(str[0], ft_getenv("HOME"), strlen(ft_getenv("HOME"))) == 0)
		str[1] = ft_strjoin("~", str[0] + strlen(ft_getenv("HOME")));
	else
		str[1] = ft_strdup(str[0]);
	free(str[0]);
	str[0] = colorize(str[1], YELLOW);
	free(str[1]);
	str[1] = ft_strjoin(" ", str[0]);
	free(str[0]);
	str[0] = ft_strjoin(str[1], " ");
	free(str[1]);
	return (str[0]);
}

int	get_term_width(void)
{
	struct winsize	ws;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	return (ws.ws_col);
}

char	*get_exit_status(void)
{
	char	*str[3];

	if (g_data.exit_status != 0)
		str[0] = ft_itoa(g_data.exit_status);
	else
		str[0] = ft_strdup("✔");
	if (g_data.exit_status != 0)
		str[1] = colorize(str[0], RED);
	else
		str[1] = colorize(str[0], GREEN);
	free(str[0]);
	str[0] = ft_strjoin(str[1], RESET);
	free(str[1]);
	str[1] = get_output((char *[]){"/usr/bin/date", "+%H:%M:%S %p", NULL});
	str[2] = ft_strjoin(str[1], "  ");
	free(str[1]);
	str[1] = ft_strjoin(" ", str[2]);
	free(str[2]);
	str[2] = ft_strjoin(str[0], str[1]);
	return (free(str[0]), free(str[1]), str[2]);
}

static
char	*read_branch(int *fd, int status)
{
	char	*str[2];
	char	*branch;

	str[0] = NULL;
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		str[0] = get_next_line(fd[0]);
	close_pipe(fd);
	if (!str[0])
		return (g_data.branch = false, NULL);
	str[0][ft_strlen(str[0]) - 1] = '\0';
	str[1] = ft_strjoin("(", str[0]);
	free(str[0]);
	str[0] = ft_strjoin(str[1], ")");
	branch = colorize(str[0], GREEN);
	free(str[0]);
	free(str[1]);
	g_data.branch = true;
	return (branch);
}

char	*get_branch(void)
{
	pid_t	pid;
	int		status;
	int		fd[3];

	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		fd[2] = open("/dev/null", O_WRONLY);
		dup2(fd[2], STDERR_FILENO);
		close(fd[2]);
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		execve("/usr/bin/git", (char *[]){"git", "branch", "--show-current",
			NULL}, g_data.environ);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (read_branch(fd, status));
}
