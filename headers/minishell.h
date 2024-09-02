/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 11:33:00 by akhobba          ###   ########.fr       */
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
// # include <bsd/string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

// Prompt stuff & colors
# define NAME "\033[1;31mminishell\033[0m: "
# define PROMPT "\033[1;36mminishell\033[0m:> "
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

// Define default PATH
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

// global variable
extern struct s_data	g_data;

typedef struct s_link
{
	char			*command;
	int				identifier;
	struct s_link	*prev;
	struct s_link	*next;
}					t_link;

typedef struct s_redirection
{
	int						identifier;
	char					*file;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmd
{
	int						argc;
	char					**argv;
	struct s_redirection	*redirections;
}							t_cmd;

typedef struct s_tree
{
	int						type;
	struct s_cmd			*cmd;
	struct s_tree			*prev;
	struct s_tree			*left;
	struct s_tree			*right;
	struct s_redirection	*redirection;
}							t_tree;

typedef struct s_data
{
	char			*path;
	struct s_tree	*tree;
	char			**environ;
	char			*input;
	char			*prompt;
	int				exit_status;
}					t_data;

#endif
