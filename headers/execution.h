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

// builtins
bool	cd(t_cmd *cmd);
bool	echo(t_cmd *cmd);
bool	pwd(void);

#endif //EXECUTION_H
