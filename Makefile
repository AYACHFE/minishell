# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 13:44:57 by aachfenn          #+#    #+#              #
#    Updated: 2023/05/16 15:30:00 by rarraji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= src/minishell_1.c \
		  src/command.c \
		  

CC		= cc 

CFLAGS	= -Wall -Wextra -Werror 

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
