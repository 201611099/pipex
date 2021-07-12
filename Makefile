# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2021/07/13 00:04:23 by lhj-unix         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
LIB_NAME = libft.a
LIB_DIR = ./libft
INC = ./

SRCS = pipex.c pipex_utils.c
OBJS = $(SRCS:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIB_DIR)/
	@cp $(LIB_DIR)/$(LIB_NAME) $(LIB_NAME)
	@$(CC) $(CFLAGS) -I$(INC) -o $(NAME) $(OBJS) $(LIB_NAME)

clean:
	@$(MAKE) clean -C $(LIB_DIR)/
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIB_DIR)/
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
