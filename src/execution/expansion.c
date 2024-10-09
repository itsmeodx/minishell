/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:57:17 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 19:11:32 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	printf_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("printf_lst: %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

char	**expand_argv(t_list *argv_lst)
{
	char	**argv;
	char	**tmp;
	t_list	*lst;

	argv = NULL;
	while (argv_lst)
	{
		lst = argv_lst->content;
		tmp = lst_to_argv(lst);
		ft_lstclear(&lst, free);
		argv = ft_strjoin_2d(argv, tmp);
		free_2d(tmp);
		argv_lst->content = NULL;
		argv_lst = argv_lst->next;
	}
	return (argv);
}

static
void	ft_alias_expansion(char **str)
{
	char	*tmp;

	if (!str || !*str || !is_in_env(*str, g_data()->aliases))
		return ;
	tmp = ft_getenv(*str, g_data()->aliases);
	free(*str);
	*str = ft_strdup(tmp);
}

void	ft_expansion(t_cmd *cmd)
{
	int		i;
	t_list	*lst;
	t_list	*argv_lst;

	lst = NULL;
	argv_lst = NULL;
	i = -1;
	ft_alias_expansion(&cmd->argv[0]);
	while (cmd->argv && cmd->argv[++i])
	{
		ft_expanding(&lst, cmd->argv[i]);
		ft_lstadd_back(&argv_lst, ft_lstnew(lst));
		lst = NULL;
	}
	free(cmd->argv);
	cmd->argv = expand_argv(argv_lst);
	cmd->argc = ft_strlen_2d(cmd->argv);
	ft_lstclear(&argv_lst, free);
}
