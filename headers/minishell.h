/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 18:02:03 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_printf.h"
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
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <bsd/string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

// Prompt stuff & colors
# define NAME "\001\033[1;31m\002minishell\001\033[0m\002: "
# define PROMPT "\001\033[1;36m\002minishell\001\033[0m\002:> "
# define RED "\001\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define MAGENTA "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define GRAY "\001\033[1;37m\002"
# define BOLD "\001\033[1m\002"
# define UNDERLINE "\001\033[4m\002"
# define BLINK "\001\033[5m\002"
# define REVERSE "\001\033[7m\002"
# define HIDDEN "\001\033[8m\002"
# define WHITE "\001\033[1;37m\002"
# define BLACK "\001\033[1;30m\002"
# define RESET "\001\033[0m\002"

// heardoc
# define HEREDOC_PREFIX "/tmp/hd_"
# define HEREDOC_PROMPT "> "

// Define default PATH
# define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

// global variable
struct s_data	*g_data(void);

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
	struct s_redirection	*redirections;
}							t_tree;

typedef struct s_garbage
{
	t_link				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_data
{
	int					hfd;
	char				*path;
	char				**aliases;
	struct s_tree		*tree;
	bool				branch;
	char				*input;
	char				*last_line;
	char				*home;
	char				**environ;
	unsigned char		exit_status;
	struct s_garbage	*garbage;
}						t_data;

#endif
