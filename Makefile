# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 13:44:57 by aachfenn          #+#    #+#              #
#    Updated: 2023/05/24 19:39:11 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= src/minishell_1.c src/built_in.c src/command.c src/unset.c src/ft_export.c \
			parcing/parce_1.c parcing/parce_2.c

CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g

OBJ		= ${SRC:.c=.o}

NAME	= minishell

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJ}
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
