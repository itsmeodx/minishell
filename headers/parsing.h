/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 12:35:04 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "minishell.h"
# define LEN_ENUM 8

typedef enum e_type
{
	STR,
	IN,
	OUT,
	APPEND,
	HERDOC,
	PIPE,
	OR,
	AND,
	OPEN_PAR,
	CLOSE_PAR
}				t_type;

typedef enum e_errorn
{
	NONE,
	ERROR_IN,
	ERROR_APPEND,
	ERROR_OUT,
	ERROR_HERDOC,
	ERROR_PIPE,
	ERROR_SIGNAL_QUOTE,
	ERROR_DOUBLE_QUOTE,
	ERROR_OR,
	ERROR_AND,
	ERROR_OPEN_PAREN,
	ERROR_CLOSE_PAREN
}				t_errorn;

/* error guide
	0: error in less(in) redirection
	1: error in lessless(out) redirection
	2: error in great(append) redirection
	3: error in greatgreat(append) redirection
	4: error in pipe redirection
	5: error in command (no command found)
	6 : error in or (||)
	7 : error in and (&&)
	8 : error in open parenthesis
	9 : error in close parenthesis
*/

// typedef struct s_error
// {
// 	t_errorn		error;
// 	struct s_error	*next;
// }					t_error;

//extern t_error	*g_error; // global variable to store errors

// old linked list will be replaced by a new tree

/*Parsing*/
// src
char			**ft_lexer(char *input);
char			**ft_split(char *str, char *c);
int				check_quote(char *str, int a);
int				ft_strlen(const char *str);
int				ft_strchr(int c, const char *s);
t_tree			*ft_parsing(char *input);
t_link			*ft_def_type(char **input);
t_link			*ft_find_hightest_proirity(t_link *head);
int				ft_redirections(t_link *link, t_redirection **redirectoin);
char			**ft_strjoin_2d(char **s1, char **s2);

// **tree_ft**
void			ft_treeadd_back_left(t_tree **tree, t_tree *new);
t_tree			*ft_treenew(char *cmd, int type);
t_cmd			*ft_cmdnew(char *cmd);
void			ft_treeadd_back_right(t_tree **tree, t_tree *new);
t_tree			*ft_create_tree(t_tree **tree, t_link *link);
void			ft_print_cmd(t_tree *tree);
void			ft_printf_tree(t_tree *tree, int space, int option);
void			ft_generate_spaces(int n);
void			ft_add_to_argv(t_tree **new, char *command);
void			ft_cmd_create(t_tree **new, t_link *link);
t_tree			*ft_parse_and_or(t_link *link);
t_tree			*ft_parse_parenthesis(t_tree **tree, t_link *link);
void			ft_limit_link(t_link **link);
void			ft_treeclear(t_tree *tree);
// src fts
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// // utils
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr_v2(const char *s, int c);
void			free_2d(char **tab);
char			**ft_strdup_2d(char **s);
char			*ft_strdup(const char *s);
int				ft_count_strs(char **s);
int				ft_strlen(const char *str);
char			*ft_strjoin(char *s1, char const *s2);
char			*ft_strdup(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

// // rediction_ft
t_redirection	*ft_lstnew_redi(char *content);
void			ft_lstadd_back_redi(t_redirection **list, t_redirection *node);
void			ft_lstclear_redi(t_redirection **list);

// // link_ft
t_link			*ft_create_new_link(t_link *link, t_link *limit);
t_link			*ft_search_target(t_link *head, int target[2]);
void			ft_printf_link(t_link *link);

// dbl link_ft
void			ft_dbl_lstadd_back(t_link **lst, t_link *new);
t_link			*ft_dbl_lstnew(void *content);
t_link			*ft_dbl_lstlast(t_link *lst);
void			ft_dbl_lstclear(t_link **lst);

// Syntax error fts
t_errorn		ft_check_quotes(t_link *link);
t_errorn		ft_check_and_or(t_link *link);
t_errorn		ft_check_pipe(t_link *link);
t_errorn		ft_check_in(t_link *link);
t_errorn		ft_check_out(t_link *link);
t_errorn		ft_check_append(t_link *link);
t_errorn		ft_check_herdoc(t_link *link);
t_errorn		ft_check_parentheses(t_link *link);
int				ft_syntax_error(t_link *link);
void			ft_printf_error(t_errorn error);

#endif // PARSING_H
