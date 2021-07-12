/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:56:13 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/13 00:34:30 by lhj-unix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_cmd
{
	char	*cmd;
	char	**opt;
	char	*path;
}	t_cmd;

typedef struct	s_file
{
	char	*name;
	int	fd;
	int	exist;
}	t_file;

typedef struct	s_arg
{
	t_file	input;
	t_file	output;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_arg;

void	print_err(char *str, int exit_status);
void	free_all(t_arg *arg, char **path);
void	set_fdtable(t_arg *arg);
void	start_pipe(t_arg *arg);

#endif
