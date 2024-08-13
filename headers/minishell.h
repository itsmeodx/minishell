/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/07/30 11:52:02 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ctype.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <bsd/string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NAME "minishell: "
# define PROMPT "\033[1;32mminishell:>\033[0m "
# define PROMPT_SIZE 11
# define MAX_PATH 4096
# define MAX_CMD 4096
# define MAX_ENV 4096
# define MAX_HISTORY 1000
# define MAX_BUILTINS 7
# define MAX_REDIRECT 3
# define MAX_PIPE 2
# define NSFOD "No such file or directory"

typedef struct s_cmd
{
	int		argc;
	char	**argv;
}	t_cmd;

#endif //MINISHELL_H
