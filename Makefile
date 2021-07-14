# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2021/07/14 20:19:48 by hyojlee          ###   ########.fr        #
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

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIB_DIR)
	@$(CC) $(CFLAGS) -I$(INC) -o $(NAME) $(OBJS) $(LIB_DIR)$(LIB_NAME)

clean:
	@$(MAKE) clean -C $(LIB_DIR)
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIB_DIR)
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
