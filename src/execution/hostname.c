/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:20:32 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:29:25 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	set_hostname(char **env)
{
	int		i;
	int		fd;
	char	*hostname;

	fd = open("/etc/hostname", O_RDONLY);
	hostname = get_next_line(fd);
	close(fd);
	if (!hostname)
		hostname = ft_strdup("localhost");
	i = 0;
	while (isalnum(hostname[i]) || hostname[i] == '-')
		i++;
	hostname[i] = 0;
	if (is_in_env("MINI_HOSTNAME", env))
		update_env(env, "MINI_HOSTNAME", hostname);
	else
		g_data()->environ = addtoenv(env, "MINI_HOSTNAME", hostname);
	free(hostname);
}
