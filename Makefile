# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 16:47:21 by oouaadic          #+#    #+#              #
#    Updated: 2024/09/09 15:16:05 by akhobba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address,leak,undefined
INC			=	-I./headers
HEADERS		=	headers/minishell.h headers/execution.h headers/parsing.h
SRCDIR		=	src
OBJDIR		=	obj

#Colors
RED			=	\e[1;31m
GREEN		=	\e[1;32m
YELLOW		=	\e[3;33m
CYAN		=	\e[3;96m
END			=	\e[0m

PARSING		=	parsing/lexer parsing/parser\
				parsing/utils/ft_strlen parsing/utils/ft_split \
				parsing/tree_utils/ft_treenew parsing/create_tree \
				parsing/utils/ft_strchr parsing/utils/ft_strdup \
				parsing/utils/double_list/ft_dbl_lstnew_bonus \
				parsing/utils/double_list/ft_dbl_lstadd_back_bonus \
				parsing/utils/double_list/ft_dbl_lstlast_bonus \
				parsing/utils/double_list/ft_dbl_lstclear_bonus \
				parsing/utils/ft_strncmp parsing/utils/small_ft \
				parsing/search parsing/printf_tree parsing/create_cmd \
				parsing/redirections parsing/utils/ft_lst_redi \
				parsing/parse_parentheses parsing/tree_utils/ft_treeclear \
				parsing/quotes_checker parsing/syntax_error \
				parsing/and_or_checker parsing/redirections_checker \
				parsing/parentheses_checker parsing/open_herdoc\
				parsing/utils/ft_strlcat parsing/garbage_collector\
				parsing/signal \

EXECUTION	=	execution/builtins/builtins execution/builtins/cd \
				execution/builtins/echo execution/builtins/exit \
				execution/builtins/export execution/builtins/unset \
				 execution/builtins/pwd \
				execution/env execution/exec execution/execute_and_or \
				execution/execute_par execution/execute_pipe \
				execution/execute_str execution/execution execution/expansion \
				execution/ft_readline execution/gnl execution/history \
				execution/hostname execution/prompt \
				execution/redirections execution/utils/close_pipe \
				execution/utils/extend_2d execution/utils/ft_itoa \
				execution/utils/ft_substr execution/utils/prompt_utils

SRC			=	$(addprefix $(SRCDIR)/, main.c) \
				$(addprefix $(SRCDIR)/, $(addsuffix .c, $(PARSING))) \
				$(addprefix $(SRCDIR)/, $(addsuffix .c, $(EXECUTION)))

OBJ			=	$(addprefix $(OBJDIR)/, main.o) \
				$(addprefix $(OBJDIR)/, $(addsuffix .o, $(PARSING))) \
				$(addprefix $(OBJDIR)/, $(addsuffix .o, $(EXECUTION)))

INC = -I./headers

NAME = minishell

all: $(NAME)

norm:
	@norminette --use-gitignore . > /dev/null || (echo "$(RED)Norminette failed$(END)" && exit 1)
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Norminette passed$(END)"; fi

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling $(CYAN)$(NAME)$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) -lreadline
	@echo "$(CYAN)$(NAME) is ready to use$(END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@echo "$(YELLOW)Compiling $(CYAN)$(notdir $<)$(END)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(GREEN)Done.$(END)"

clean:
	@echo "$(RED)Cleaning $(OBJDIR)...$(END)"
	@$(RM) -r $(OBJDIR) || true

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(END)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean NORM
