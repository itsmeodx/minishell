/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:44:48 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 16:44:48 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

int	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (EXIT_SUCCESS);
}
