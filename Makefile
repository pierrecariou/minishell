# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:17:20 by pcariou           #+#    #+#              #
#    Updated: 2020/10/12 16:35:15 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

HEADER		= ./

SRCS		=	srcs/main.c \
				srcs/init_path.c \
				srcs/get_commands.c \
				srcs/find_path.c \
				srcs/pipeline.c \
				srcs/error.c \
				utils/gnl/get_next_line.c \
				utils/gnl/get_next_line_utils.c

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

AR			=  ar rcs

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

ATTRIBUT	= -c

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) $(ATTRIBUT) $< -o $(<:.c=.o) -I$(HEADER)

$(NAME):	$(OBJS)
			#$(AR) minishell.o $(OBJS) && cd libft && make
			#$(CC) $(CFLAGS) -o $(NAME) minishell.o
			#$(RM) minishell.o
			cd utils/libft && make
			$(CC) -o $(NAME) $(OBJS) utils/libft/libft
clean:
			$(RM) $(OBJS) && cd utils/libft && make clean

fclean:		clean
			$(RM) $(NAME) && cd utils/libft && make fclean

re:			fclean all

.PHONY:		all clean fclean re

