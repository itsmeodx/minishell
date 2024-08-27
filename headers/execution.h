/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/13 11:11:37 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

// builtins/
bool	is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd);
bool	builtin_cd(t_cmd *cmd);
bool	builtin_echo(t_cmd *cmd);
bool	builtin_exit(t_cmd *cmd);
bool	builtin_export(t_cmd *cmd);
bool	builtin_pwd(t_cmd *cmd);

// utils/
void	*extend_2d(char **ptr, size_t size);
char	*ft_itoa(int n);

// env.c
void	update_shlvl(char **env);
void	update_env(char **env, char *key, char *value);

// execute_and_or.c
int		execute_and(t_tree *tree);
int		execute_or(t_tree *tree);

// execute_par.c
int		execute_par(t_tree *tree);

// execute_pipe.c
int		first_child(int *fd, t_tree *tree);
int		second_child(int *fd, t_tree *tree);
int		execute_pipe(t_tree *tree);

// execute_str.c
int		execute_cmd(t_cmd *cmd);
int		execute_str(t_tree *tree);

// execution.c
int		ft_execution(t_tree *tree);

// prompt.c
char	*colorize(char *str, char *color);
char	*ft_getprompt(void);

// sysutils.c
int		close_pipe(int *fd);

#endif //EXECUTION_H
