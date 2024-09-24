# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/31 16:47:21 by oouaadic          #+#    #+#              #
#    Updated: 2024/09/24 21:50:57 by akhobba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g3 -fsanitize=address,leak,undefined
INC				=	-I./headers
HEADERS			=	headers/minishell.h headers/execution.h headers/parsing.h
SRCDIR			=	src
OBJDIR			=	obj

#libftprintf
FT_PRINTF		=	ft_printf/libftprintf.a
FT_PRINTF_DIR	=	ft_printf

#Colors
RED				=	\e[1;31m
GREEN			=	\e[1;32m
YELLOW			=	\e[3;33m
CYAN			=	\e[3;96m
END				=	\e[0m

PARSING			=	parsing/lexer parsing/parser\
					parsing/utils/ft_qsplit parsing/utils/ft_strchr_v2\
					parsing/tree_utils/ft_treenew parsing/create_tree \
					parsing/utils/ft_strdup \
					parsing/utils/double_list/ft_dbl_lstnew_bonus \
					parsing/utils/double_list/ft_dbl_lstadd_back_bonus \
					parsing/utils/double_list/ft_dbl_lstlast_bonus \
					parsing/utils/double_list/ft_dbl_lstclear_bonus \
					parsing/utils/small_ft \
					parsing/search parsing/printf_tree parsing/create_cmd \
					parsing/redirections parsing/utils/ft_lst_redi \
					parsing/parse_parentheses parsing/tree_utils/ft_treeclear \
					parsing/quotes_checker parsing/syntax_error \
					parsing/and_or_checker parsing/redirections_checker \
					parsing/parentheses_checker parsing/open_heredoc\
					parsing/garbage_collector parsing/rm_quotes \

EXECUTION		=	execution/builtins/builtins execution/builtins/cd \
					execution/builtins/echo execution/builtins/env \
					execution/builtins/exit \
					execution/builtins/export execution/builtins/unset \
					execution/builtins/pwd execution/asterisk \
					execution/env execution/exec \
					execution/execute_and_or \
					execution/execute_par execution/execute_pipe \
					execution/execute_str execution/execution execution/expanding \
					execution/expansion \
					execution/ft_readline execution/gnl execution/history \
					execution/hostname execution/init execution/prompt \
					execution/quotes \
					execution/redirections execution/signal execution/utils/asterisk_utils \
					execution/utils/close_pipe \
					execution/utils/dir_utils \
					execution/utils/env_utils execution/utils/env_utils_2 \
					execution/utils/extend_2d execution/utils/ft_itoa \
					execution/utils/ft_lstexpand execution/utils/ft_splits \
					execution/utils/ft_substr execution/utils/lst_utils \
					execution/utils/output_utils \
					execution/utils/prompt_utils

SRC				=	$(addprefix $(SRCDIR)/, main.c) \
					$(addprefix $(SRCDIR)/, $(addsuffix .c, $(PARSING))) \
					$(addprefix $(SRCDIR)/, $(addsuffix .c, $(EXECUTION)))

OBJ				=	$(addprefix $(OBJDIR)/, main.o) \
					$(addprefix $(OBJDIR)/, $(addsuffix .o, $(PARSING))) \
					$(addprefix $(OBJDIR)/, $(addsuffix .o, $(EXECUTION)))

INC = -I./headers -I./ft_printf/headers -I./ft_printf/Libft/headers

NAME = minishell

all: $(NAME)

norm:
	@norminette --use-gitignore . > /dev/null || (echo "$(RED)Norminette failed$(END)" && exit 1)
	@if [ $$? -eq 0 ]; then echo "$(GREEN)Norminette passed$(END)"; fi

$(NAME): $(FT_PRINTF) $(OBJ)
	@echo "$(YELLOW)Compiling $(CYAN)$(NAME)$(END)"
	@$(CC) $(CFLAGS) $(OBJ) $(FT_PRINTF) $(INC) -o $(NAME) -lreadline
	@echo "$(CYAN)$(NAME) is ready to use$(END)"

$(FT_PRINTF):
	@echo "$(YELLOW)Compiling $(CYAN)libftprintf.a$(END)"
	@make -C $(FT_PRINTF_DIR) > /dev/null
	@echo "$(GREEN)Done.$(END)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@echo "$(YELLOW)Compiling $(CYAN)$(notdir $<)$(END)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(GREEN)Done.$(END)"

clean:
	@echo "$(RED)Cleaning $(OBJDIR)...$(END)"
	@make -C $(FT_PRINTF_DIR) clean > /dev/null
	@$(RM) -r $(OBJDIR) || true

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(END)"
	@make -C $(FT_PRINTF_DIR) fclean > /dev/null
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean norm
