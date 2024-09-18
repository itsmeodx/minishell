/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/18 10:14:28 by oouaadic         ###   ########.fr       */
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
# define NVI "not a valid identifier"

// builtins/
// builtins.c
int				execute_builtin(t_cmd *cmd);
// cd.c
bool			builtin_cd(t_cmd *cmd);
// echo.c
bool			builtin_echo(t_cmd *cmd);
// env.c
bool			builtin_env(t_cmd *cmd);
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
// asterisk_utils.c
char			*get_prefix(char *str, int i);
char			**get_midfix(char *str, int i);
char			*get_suffix(char *str, int i);
bool			check_midfix(char *entry, char *prefix, char **midfix,
					char *suffix);
// close_pipe.c
int				close_pipe(int *fd);
// dir_utils.c
bool			isdir(char *path);
int				dir_size(char *dirname);
char			**get_entries(void);
// env_utils.c
char			*get_home(void);
char			**var_split(char *var);
bool			is_valid_key(char *key, bool *bad_key);
char			**remove_from_env(char **env, char *key);
char			**filter_env(char **env);
// env_utils_2.c
void			sort_2d(char **strs);
char			*expand_val(char *str, char *value, int *i);
char			*expand_dollar(char *str);
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
// output_utils.c
char			*get_output(char **cmd);

// asterisk.c
char			*expand_asterisk(char *str);
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
char			*expand_status(char *str, int *i);
void			ft_expansion(t_cmd *cmd);

// expanding.c
char			*ft_expanding(char *str);

// ft_readline.c
char			*ft_readline(char *prompt);

// gnl.c
char			*get_next_line(int fd);

// history.c
void			ft_add_history(char *line);
void			restore_history(void);

// hostname.c
void			set_hostname(char **env);

// init.c
void			init_minishell(char **env);

// prompt.c
char			*colorize(char *str, char *color);
char			*ft_getprompt(void);
char			*create_full_prompt(void);

// quotes.c
int				is_in_quote(char *str, int i);
int				get_next_quote(char *str, char quote);

// redirections.c
bool			set_redirections(t_redirection *redirections);

// signals.c
bool			reset_signals(void);
void			ft_signal(int sig);

#endif //EXECUTION_H
