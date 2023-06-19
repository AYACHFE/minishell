# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 13:44:57 by aachfenn          #+#    #+#              #
#    Updated: 2023/06/19 13:16:33 by aachfenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/minishell_1.c src/built_in.c src/command.c src/unset.c \
			parcing/parce_1.c parcing/parce_2.c errors/errors_1.c \
			errors/errors_2.c execution/exec_1.c src/exit.c execution/expantion_heredoc.c \
			src/leaks.c execution/here_doc.c execution/file_creation.c execution/exec_2.c \
			execution/exec_3.c parcing/parce_1_ext.c parcing/parce_2_ext.c src/built_in_ext.c \
			errors/errors_2_ext.c ft_export/ft_export_1.c ft_export/ft_export_2.c \
			ft_export/ft_export_3.c ft_export/ft_export_4.c expanding/expantion.c \
			expanding/expantion_2.c src/command_2.c src/command_3.c expanding/expantion_3.c\
			execution/here_doc_2.c errors/errors_1.1_ext.c \
			errors/error_1.2_ext.c errors/errors_2.1.c errors/error_1.3_ext.c 

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

OBJ		= ${SRC:.c=.o}

NAME	= minishell

RLFLAGS =	-L/Users/aachfenn/goinfre/homebrew/opt/readline/lib

RLINCLUDE	=	-I/Users/aachfenn/goinfre/homebrew/opt/readline/include/

%.o : %.c Makefile
	${CC} ${CFLAGS} -c $< -o $@ $(RLINCLUDE)
	 
	
${NAME}	:	${OBJ} minishell.h
		make -C utils/ft_libft
		${CC} ${CFLAGS} ${OBJ} utils/ft_libft/libft.a -o ${NAME} -lreadline $(RLFLAGS)

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
