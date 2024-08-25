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
bool	execute_builtin(t_cmd *cmd);
bool	builtin_cd(t_cmd *cmd);
bool	builtin_echo(t_cmd *cmd);
bool	builtin_pwd(void);
bool	builtin_exit(t_cmd *cmd);

#endif //EXECUTION_H
