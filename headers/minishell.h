/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/23 11:13:40 by akhobba          ###   ########.fr       */
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
# include <errno.h>

# define NAME "\033[1;31mminishell: \033[0m"
# define PROMPT "\033[1;32mminishell:>\033[0m "
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

# define PROMPT_SIZE 11
# define MAX_PATH 4096
# define MAX_CMD 4096
# define MAX_ENV 4096
# define MAX_HISTORY 1000
# define MAX_BUILTINS 7
# define MAX_REDIRECT 3
# define MAX_PIPE 2

# define NSFOD "No such file or directory"
# define CNF "command not found"
# define PD "Permission denied"
# define TMA "too many arguments"
# define NAR "numeric argument required"

typedef struct s_link
{
	char			*command;
	int				identifier;
	struct s_link	*prev;
	struct s_link	*next;
}					t_link;

typedef struct s_cmd
{
	int				argc;
	char			**argv;
}					t_cmd;

typedef struct s_redirection
{
	int						identifier;
	char					*file;
	struct s_redirection	*next;
}					t_redirection;

typedef struct s_tree
{
	int				type;
	t_cmd			*cmd;
	int				exit_status;
	t_redirection	*redirection;
	struct s_tree	*prev;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

#endif
