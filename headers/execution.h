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

// error messages
# define NSFOD "No such file or directory"
# define CNF "command not found"
# define PD "Permission denied"
# define TMA "too many arguments"
# define NAR "numeric argument required"

// builtins/
// builtins.c
bool			is_builtin(t_cmd *cmd);
int				execute_builtin(t_cmd *cmd);
// cd.c
bool			builtin_cd(t_cmd *cmd);
// echo.c
bool			builtin_echo(t_cmd *cmd);
// exit.c
int				ft_exit(int status);
bool			builtin_exit(t_cmd *cmd);
// export.c
bool			builtin_export(t_cmd *cmd);
// pwd.c
bool			builtin_pwd(t_cmd *cmd);

// utils/
// sysutils.c
int				close_pipe(int *fd);
// extend_2d.c
void			*extend_2d(char **ptr, size_t size);
// ft_itoa.c
char			*ft_itoa(int n);

// env.c
void			update_pwd(char **env);
void			update_shlvl(char **env);
void			update_env(char **env, char *key, char *value);

// execute_and_or.c
int				execute_and(t_tree *tree);
int				execute_or(t_tree *tree);

// execute_par.c
int				execute_par(t_tree *tree);

// execute_pipe.c
int				first_child(int *fd, t_tree *tree);
int				second_child(int *fd, t_tree *tree);
int				execute_pipe(t_tree *tree);

// execute_str.c
int				execute_cmd(t_cmd *cmd);
int				execute_str(t_tree *tree);

// execution.c
int				ft_execution(t_tree *tree);

// history.c
void			ft_add_history(char *line);
void			restore_history(void);

// prompt.c
char			*colorize(char *str, char *color);
char			*ft_getprompt(void);

#endif //EXECUTION_H
