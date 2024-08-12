/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/12 15:56:05 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef parsing_H
# define parsing_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_link
{
	char			*command;
	int				identifer;
	struct s_link	*prev;
	struct s_link	*next;
}					t_link;

typedef struct s_cmd
{
	int				argc;
	char			**argv;
}					t_cmd;

typedef struct s_tree
{
	int				type;
	t_cmd			*cmd;
	int				exit_status;
	struct s_tree	*prev;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

#endif