# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 10:17:20 by pcariou           #+#    #+#              #
#    Updated: 2020/10/15 11:36:00 by pcariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

HEADER		= ./

SRCS		=	srcs/main.c \
				srcs/init_path.c \
				srcs/get_commands.c \
				srcs/parse_redir.c \
				srcs/find_path.c \
				srcs/pipeline.c \
				srcs/redirect.c \
				srcs/error.c \
				utils/gnl/get_next_line.c \
				utils/gnl/get_next_line_utils.c \
				srcs/built_in/ft_cd.c \
				srcs/built_in/ft_cmp_built_in.c \
				srcs/built_in/ft_echo.c \
				srcs/built_in/ft_env.c \
				srcs/built_in/ft_pwd.c \
				srcs/built_in/ft_export.c \
				srcs/built_in/gab_le_bg.c \


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
			cd utils/libft && make
			$(CC) -o $(NAME) $(OBJS) utils/libft/libft
clean:
			$(RM) $(OBJS) && cd utils/libft && make clean

fclean:		clean
			$(RM) $(NAME) && cd utils/libft && make fclean

re:			fclean all

.PHONY:		all clean fclean re

