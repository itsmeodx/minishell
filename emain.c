/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:20:13 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/25 09:51:48 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

//char	**ft_esplit(char *str, char c)
//{
//	char	**tab;
//	int		i;
//	int		j;
//	int		k;
//
//	tab = malloc(sizeof(char *) * (strlen(str) + 1));
//	if (!tab)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (str[i])
//	{
//		if (str[i] == c)
//			i++;
//		else
//		{
//			k = i;
//			while (str[i] && str[i] != c)
//				i++;
//			tab[j] = malloc(i - k + 1);
//			if (!tab[j])
//				return (NULL);
//			strlcpy(tab[j], str + k, i - k + 1);
//			j++;
//		}
//	}
//	tab[j] = NULL;
//	return (tab);
//}
//
//void	efree_2d(char **tab)
//{
//	int	i;
//
//	i = 0;
//	while (tab[i])
//		free(tab[i++]);
//	free(tab);
//}
//
//int	count_2d(char **tab)
//{
//	int	i;
//
//	i = 0;
//	while (tab[i])
//		i++;
//	return (i);
//}

//char	*ft_estrjoin(char *s1, char *s2)
//{
//	char	*str;
//	int		i;
//	int		j;
//
//	if (!s1 || !s2)
//		return (NULL);
//	str = malloc(strlen(s1) + strlen(s2) + 1);
//	if (!str)
//		return (NULL);
//	i = 0;
//	while (s1[i])
//	{
//		str[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j])
//	{
//		str[i + j] = s2[j];
//		j++;
//	}
//	str[i + j] = '\0';
//	return (str);
//}

//char	*remove_quotes(char *str)
//{
//	char	*tmp;
//	int		i;
//	int		j;
//
//	i = 0;
//	j = 0;
//	while (str[i])
//	{
//		if (str[i] != '\'' && str[i] != '\"')
//			j++;
//		i++;
//	}
//	tmp = malloc(sizeof(char) * (j + 1));
//	if (!tmp)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (str[i])
//	{
//		if (str[i] != '\'' && str[i] != '\"')
//			tmp[j++] = str[i];
//		i++;
//	}
//	tmp[j] = '\0';
//	free(str);
//	return (tmp);
//}
//
//char	**remove_quotes_2d(char **argv)
//{
//	int		i;
//
//	i = 0;
//	while (argv[i])
//	{
//		argv[i] = remove_quotes(argv[i]);
//		if (!argv[i])
//		{
//			free_2d(argv);
//			return (NULL);
//		}
//		i++;
//	}
//	return (argv);
//}

//bool	parse_line(char *line)
//{
//	t_cmd	cmd;
//
//	cmd.argv = ft_split(line, " \t\n");
//	if (!cmd.argv)
//		return (false);
//	cmd.argv = remove_quotes_2d(cmd.argv);
//	if (!cmd.argv)
//		return (false);
//	cmd.argc = count_2d(cmd.argv);
//	if (!cmd.argv || !cmd.argv[0])
//		return (free_2d(cmd.argv), true);
//	if (is_builtin(&cmd))
//		execute_builtin(&cmd);
//	else
//		execute_cmd(&cmd);
//	free_2d(cmd.argv);
//	return (true);
//}

//void	print_prompt(void)
//{
//	char	*cwd;
//
//	cwd = getcwd(NULL, 0);
//	if (strncmp(cwd, getenv("HOME"), strlen(getenv("HOME"))) == 0)
//	{
//		printf(PROMPT"~%s ", cwd + strlen(getenv("HOME")));
//		free(cwd);
//		return ;
//	}
//	printf(PROMPT"%s ", cwd);
//	free(cwd);
//}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env __attribute__((unused)))
{
	char	*line;
	char	*prompt;
	char	**environ;
	t_tree	*tree;

	restore_history();
	__environ = ft_strdup_2d(__environ);
	environ = __environ;
	update_shlvl(environ);
	while (true)
	{
		prompt = ft_getprompt();
		line = readline(prompt);
		__environ = environ;
		free(prompt);
		if (!line)
			break ;
		if (*line)
			ft_add_history(line);
		tree = ft_parsing(line);
		free(line);
		if (tree)
			ft_execution(tree);
		ft_treeclear(tree);
	}
	free_2d(environ);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
