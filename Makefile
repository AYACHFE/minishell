# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 13:44:57 by aachfenn          #+#    #+#              #
#    Updated: 2023/06/16 20:16:01 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/minishell_1.c src/built_in.c src/command.c src/unset.c src/ft_export.c \
			parcing/parce_1.c parcing/parce_2.c parcing/expantion.c errors/errors_1.c \
			errors/errors_2.c execution/exec_1.c src/exit.c execution/expantion_heredoc.c \
			src/leaks.c execution/here_doc.c execution/file_creation.c execution/exec_2.c \
			execution/exec_3.c

CC		= cc

CFLAGS	= -Wall -Wextra -Werror  \
	#  -g -fsanitize=address

OBJ		= ${SRC:.c=.o}

NAME	= minishell

%.o : %.c Makefile
	${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJ} minishell.h
		make -C utils/ft_libft
		${CC} ${CFLAGS} ${OBJ} utils/ft_libft/libft.a -o ${NAME} -lreadline

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
