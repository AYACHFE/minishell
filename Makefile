# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 13:44:57 by aachfenn          #+#    #+#              #
#    Updated: 2023/06/02 22:46:49 by rarraji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= src/minishell_1.c src/built_in.c src/command.c src/unset.c \
		  src/ft_export.c src/error.c parcing/parce_1.c parcing/parce_2.c \
		  parcing/expanding.c execution/exec_1.c

CC		= cc

CFLAGS	= -Wall -Wextra -Werror 

# ARG2 = -lreadline -L/goinfre/rarraji/brew/opt/readline/lib

# ARG = -Iinclude  -I/goinfre/rarraji/brew/opt/readline/include

OBJ		= ${SRC:.c=.o}

NAME	= minishell

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

#$(ARG) 

${NAME}	:	${OBJ}
		make -C utils/ft_libft
		${CC} ${CFLAGS} ${OBJ} utils/ft_libft/libft.a -o ${NAME} -lreadline   
#ARG2

all		: ${NAME}

clean	:
		${RM} ${OBJ}
		make clean -C utils/ft_libft

fclean	:	clean
		make fclean -C utils/ft_libft
		${RM} minishell

it		:	all
			./minishell

re		: fclean all