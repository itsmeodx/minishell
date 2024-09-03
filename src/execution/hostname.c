/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:20:32 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/03 14:20:32 by oouaadic         ###   ########.fr       */
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
	g_data.environ = addtoenv(env, "HOSTNAME", hostname);
	free(hostname);
}
