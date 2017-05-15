# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 11:23:48 by rbohmert          #+#    #+#              #
#    Updated: 2017/05/15 21:29:15 by rbohmert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME = minishell

LIB = libft/libft.a

SRC = minishell.c builtins.c utils.c utils2.c env.c setenv.c arg.c arg2.c\

GCC = gcc -o $(NAME) -Wall -Wextra -Werror -I/usr/include/

all: $(NAME)

$(NAME):
		make -C libft/
		$(GCC) $(SRC) $(LIB)

clean:
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
