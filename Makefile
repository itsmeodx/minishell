# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 23:00:54 by adam              #+#    #+#              #
#    Updated: 2024/08/31 17:50:30 by akhobba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

SRC = src/main.c \
	src/parsing/lexer.c \
	src/parsing/utils/ft_strlen.c src/parsing/utils/ft_split.c \
	src/parsing/parser.c\
	src/parsing/tree_utils/ft_treenew.c src/parsing/create_tree.c \
	src/parsing/utils/ft_strchr.c src/parsing/utils/ft_strdup.c \
	src/parsing/utils/double_list/ft_dbl_lstnew_bonus.c \
	src/parsing/utils/double_list/ft_dbl_lstadd_back_bonus.c \
	src/parsing/utils/double_list/ft_dbl_lstlast_bonus.c \
	src/parsing/utils/double_list/ft_dbl_lstclear_bonus.c \
	src/parsing/utils/ft_strncmp.c src/parsing/utils/small_ft.c \
	src/parsing/search.c src/parsing/printf_tree.c src/parsing/create_cmd.c \
	src/parsing/redirections.c src/parsing/utils/ft_lst_redi.c \
	src/parsing/parse_parenthesis.c src/parsing/tree_utils/ft_treeclear.c \
	src/parsing/quotes_checker.c \

OBJ = ${SRC:.c=.o}

INC = -I./headers

NAME = minishell

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ} -lreadline

%.o: %.c
	${CC} ${CFLAGS} $(INC) -c $< -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
