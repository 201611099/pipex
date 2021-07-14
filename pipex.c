/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:46:38 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/15 02:07:52 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_err(char *str, int exit_status)
{
	perror(str);
	exit(exit_status);
}

static char	*get_env_path(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=/", ft_strlen(*env)))
			return (*env + 5);
		env++;
	}
	if (!*env)
		print_err("PATH", 1);
	return (0);
}

static void    start_pipe(t_arg *arg, char **path, char **env)
{
        int     fd[2];
        int     pid;

        if (pipe(fd))
                print_err("pipe", 1);
        pid = fork();
        if (pid < 0)
                print_err("fork", 1);
        else if (pid > 0)
        {
                dup2(fd[0], 0);
                close(fd[1]);
		if (!arg->input.exist)
			unlink(arg->input.name);
			waitpid(pid, NULL, WNOHANG);
		set_cmdinfo(&(arg->cmd2), path);
                execve(arg->cmd2.path, arg->cmd2.opt, env);
        }
        else
        {
                dup2(fd[1], 1);
                close(fd[0]);
		set_cmdinfo(&(arg->cmd1), path);
                execve(arg->cmd1.path, arg->cmd1.opt, env);
        }
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	t_arg	arg;

	if (argc != 5)
	{
		ft_putendl_fd("Usage ./pipex file1 cmd1 cmd2 file2", 1);
		return (1);
	}
	path = ft_split(get_env_path(envp), ':');
	set_arg(&arg, argc, argv);
	start_pipe(&arg, path, envp);
	return (0);
}
