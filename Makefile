# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2021/07/15 13:28:58 by yunslee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
LIB_DIR = ./libft/
LIB_NAME = libft.a
INC = ./

SRCS = pipex.c pipex_set.c
OBJS = $(SRCS:.c=.o)

all: library $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

library:
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I$(INC) -o $(NAME) $(OBJS) $(LIB_DIR)$(LIB_NAME)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
