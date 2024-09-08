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
# define ISDIR "Is a directory"

// builtins/
// builtins.c
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
// unset.c
bool			builtin_unset(t_cmd *cmd);

// utils/
// sysutils.c
int				close_pipe(int *fd);
// env_utils.c
char			**var_split(char *var);
char			**remove_from_env(char **env, char *key);
char			**filter_env(char **env);
// extend_2d.c
void			*extend_2d(char **ptr, size_t size);
// ft_itoa.c
char			*ft_itoa(int n);
// ft_substr.c
char			*ft_substr(char const *s, unsigned int start, size_t len);
// prompt_utils.c
char			*getpwd(void);
int				get_term_width(void);
char			*get_exit_status(void);
char			*get_branch(void);

// date.c
char			*set_date(void);

// env.c
bool			is_in_env(char *key);
char			*ft_getenv(char *name);
char			**addtoenv(char **env, char *key, char *value);
void			update_pwd(char **env);
void			update_env(char **env, char *key, char *value);

// exec.c
int				ft_execvpe(char *file, char **argv, char **env);

// execute_and_or.c
int				execute_and(t_tree *tree);
int				execute_or(t_tree *tree);

// execute_par.c
int				execute_par(t_tree *tree);

// execute_pipe.c
int				execute_pipe(t_tree *tree);

// execute_str.c
int				execute_cmd(t_cmd *cmd);
int				execute_str(t_tree *tree);

// execution.c
int				ft_execution(t_tree *tree);

// expansion.c
void			ft_expansion(char **str);

// ft_readline.c
char			*ft_readline(char *prompt);

// gnl.c
char			*get_next_line(int fd);

// history.c
void			ft_add_history(char *line);
void			restore_history(void);

// hostname.c
void			set_hostname(char **env);

// main.c
void			init_minishell(char **env);

// prompt.c
char			*colorize(char *str, char *color);
char			*ft_getprompt(void);
char			*create_full_prompt(void);

// redirections.c
bool			set_redirections(t_redirection *redirections);

#endif //EXECUTION_H
