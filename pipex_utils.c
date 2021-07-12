/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhj-unix <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 22:29:50 by lhj-unix          #+#    #+#             */
/*   Updated: 2021/07/13 00:34:17 by lhj-unix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err(char *str, int exit_status)
{
	perror(str);
	exit(exit_status);
}

void	free_all(t_arg *arg, char **path)
{
	while (*path)
	{
		free(*path);
		path++;
	}
	free(path);
	free(arg->cmd1.cmd);
	free(arg->cmd2.cmd);
	while (*(arg->cmd1.opt))
	{
		free(*(arg->cmd1.opt));
		arg->cmd1.opt++;
	}
	while (*(arg->cmd2.opt))
	{
		free(*(arg->cmd2.opt));
		arg->cmd2.opt++;
	}
	free(arg->cmd1.opt);
	free(arg->cmd2.opt);
	free(arg->cmd1.path);
	free(arg->cmd2.path);
}

void	set_fdtable(t_arg *arg)
{
	dup2(arg->input.fd, 0);
	dup2(arg->output.fd, 1);
}

void	start_pipe(t_arg *arg)
{
	int	fd[2];
	int	pid;
	
	if (pipe(fd))
		print_err("pipe", 1);
	pid = fork();
	if (pid < 0)
		print_err("fork", 1);
	else if (pid > 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		waitpid(pid, NULL, 0);
		execve(arg->cmd2.path, arg->cmd2.opt, NULL);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve(arg->cmd1.path, arg->cmd1.opt, NULL);
	}
}
