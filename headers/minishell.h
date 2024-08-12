/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/11 20:49:32 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef parsing_H
# define parsing_H

# include "execution.h"
# include "parsing.h"
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	STR, //0
	IN, //1
	OUT, //2
	APPEND, //3
	HERDOC, //4
	PIPE, //5
	OR, //6
	AND, //7
    OPEN_PAR, //8
    CLOSE_PAR //9
}					t_type;

// value of each type are important to make a binary search tree
typedef struct s_cmd
{
    int     argsc;
    char    **args;
}               t_cmd;

typedef struct s_tree
{
    int                  type;
    t_cmd				*cmd; 
    int                 exit_status;
    struct s_tree		*prev;
    struct s_tree		*left;
    struct s_tree		*right;
}               t_tree;

// tree_ft
void ft_treeadd_back_left(t_tree **tree, t_tree *new);
t_tree *ft_treenew(char **cmd, int type);
t_cmd *ft_cmdnew(char **cmd);
void ft_treeadd_back_right(t_tree **tree, t_tree *new);
void ft_free_tree(t_tree *node);
t_tree *ft_create_tree(t_link *link);

#endif