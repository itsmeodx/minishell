# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adam <adam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 23:00:54 by adam              #+#    #+#              #
#    Updated: 2024/08/05 00:56:06 by adam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = #-Wall -Wextra -Werror

SRC = src/main.c src/parsing/lexer.c \
	src/utils/ft_strlen.c src/utils/ft_split.c\
	src/utils/ft_strncmp.c src/utils/small_ft.c\
	src/utils/ft_strchr.c src/utils/ft_strdup.c\
	src/utils/double_list/ft_dbl_lstnew_bonus.c \
	src/utils/double_list/ft_dbl_lstadd_back_bonus.c \
	src/utils/double_list/ft_dbl_lstlast_bonus.c \

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