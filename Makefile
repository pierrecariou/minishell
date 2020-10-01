# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:17:20 by pcariou           #+#    #+#              #
#    Updated: 2020/10/01 12:06:37 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

HEADER		= ./

SRCS		= main.c gnl/get_next_line.c gnl/get_next_line_utils.c

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
			$(AR) minishell.o $(OBJS) && cd libft && make
			$(CC) $(CFLAGS) -o $(NAME) minishell.o
			$(RM) minishell.o

clean:
			$(RM) $(OBJS) && cd libft && make clean

fclean:		clean
			$(RM) $(NAME) && cd libft && make fclean

re:			fclean all

.PHONY:		all clean fclean re

