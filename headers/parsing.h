/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/18 11:44:58 by akhobba          ###   ########.fr       */
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
	CLOSE_PAR,
	OPEN_PAR,
}					t_type;

typedef enum e_errorn
{
	ERROR_IN,
	ERROR_APPEND,
	ERROR_OUT,
	ERROR_HERDOC,
	ERROR_PIPE,
	ERROR_COMMAND,
	ERROR_QUOTE,
	ERROR_OR,
	ERROR_AND,
	ERROR_OPEN_PAR,
	ERROR_CLOSE_PAR,
}					t_errorn;

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

typedef struct s_error
{
	t_errorn		error;
	struct s_error	*next;
}					t_error;

extern t_error	*g_error; //global variable to store errors

// old linked list will be replaced by a new tree

/*Parsing*/
// src
char				**ft_lexer(char *input);
char				**ft_split(char *str, char *c);
int					check_quote(char *str, int a);
int					ft_strlen(const char *str);
int					ft_strchr(int c, const char *s);
void				ft_parsing(char *input);
t_link				*ft_def_type(char **input);
t_link				*ft_find_hightest_proirity(t_link *head);
// void						ft_check_command(t_link *link, t_command **command);
// int							ft_check_redirections(t_link *link,
// 								t_redirection **redirectoin);
// t_command					*ft_set_args(t_link *link, t_command *command);
char				**ft_strjoin_2d(char **s1, char **s2);
// int							ft_check_pipes(t_link *link,
// t_command **command);
// void						ft_main_checker(t_link *link, t_command **command);
// int							ft_quote_handler(t_link **list);
// **tree_ft**
void				ft_treeadd_back_left(t_tree **tree, t_tree *new);
t_tree				*ft_treenew(char *cmd, int type);
t_cmd				*ft_cmdnew(char *cmd);
void				ft_treeadd_back_right(t_tree **tree, t_tree *new);
void				ft_free_tree(t_tree *node);
t_tree				*ft_create_tree(t_tree **tree, t_link *link);

// // error_ft
// t_error						*ft_lstnew_error(t_errorn num_error);
// void						ft_lstadd_back_error(t_error **list, t_error *node);
// void						ft_lstclear_error(t_error **lst);
// void						ft_add_erro(t_errorn errorn);

// // command_ft
// t_command					*ft_lstnew_command(char *content);
// void						ft_lstadd_back_command(t_command **list,
// 								t_command *node);
// void						ft_lstclear_command(t_command **list);
// void						ft_free_command(t_command **command);

// // expand_ft
// int	ft_base_expand(t_link **link, env_store *env);

// src fts
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// // utils
// size_t	ft_strlcat(char *dst, const char *src, size_t size);
// char	*ft_strchr_v2(const char *s, int c);
// int							ft_count_strs(char **s);
// int							check_quote(char *str, int a);
// int							ft_error(void);
void				free_2d(char **tab);
// void						ft_free(char **str);
// void						ft_putstr(char *s, int fd);
// int							ft_isdigit(int c);
// int							ft_strncmp(const char *s1, const char *s2,
// 								size_t n);
char				**ft_strdup_2d(char **s);
char				*ft_strdup(const char *s);
int					ft_count_strs(char **s);
// int							ft_strlen(const char *str);
// long						ft_atoi(const char *nptr);
char				*ft_strjoin(char *s1, char const *s2);
// char						*ft_strdup(const char *s);
// size_t						ft_strlcpy(char *dst, const char *src,
// size_t size);

// // rediction_ft
// t_redirection				*ft_lstnew_redi(char *content);
// void						ft_lstadd_back_redi(t_redirection **list,
// 								t_redirection *node);
// void						ft_lstclear_redi(t_redirection **list);

// // link_ft
t_link				*ft_create_new_link(t_link *link, t_link *limit);
t_link				*ft_search_target(t_link *head, int target[2]);

// dbl link_ft
void				ft_dbl_lstadd_back(t_link **lst, t_link *new);
t_link				*ft_dbl_lstnew(void *content);
t_link				*ft_dbl_lstlast(t_link *lst);
void				ft_dbl_lstclear(t_link **lst);

// t_link						*ft_create_node(int nbr);
// t_link						*ft_create_node(int nbr);
// t_link						*ft_lstnew(void *content);
// void						ft_lstadd_front(t_link **lst, t_link *ne);
// int							ft_lstsize(t_link *lst);
// t_link						*ft_lstlast(t_link *lst);
// void						ft_lstadd_back(t_link **lst, t_link *ne);
// void						ft_lstclear(t_link **lst);
// void						ft_lstdelone(t_link *lst);
// void						ft_lstiter(t_link *lst, void (*f)(void *));
// t_link						*ft_lstmap(t_link *lst, void *(*f)(void *),
// void (*del)(void *));

#endif // PARSING_H
