/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:46:38 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/14 20:43:15 by lhj-unix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_fileinfo(t_arg *arg)
{
	int	flags;

	arg->output.exist = 0;
	arg->input.exist = 1;
	if (access(arg->input.name, F_OK))
		arg->input.exist = 0;
	flags = O_CREAT | O_RDONLY; 
	arg->input.fd = open(arg->input.name, flags, 0644);
	if (arg->input.fd < 0)
		print_err("open", 1);
	flags = O_CREAT | O_RDWR | O_TRUNC;
	arg->output.fd = open(arg->output.name, flags, 0644);
	if (arg->output.fd < 0)
		print_err("open", 1);
}

static void	set_cmdinfo(t_cmd *cmd, char **path)
{
	char	*cmd_path;
	char	**tmp_path;

	tmp_path = path;
	while (*tmp_path)
	{
		cmd_path = ft_strjoin(*tmp_path, cmd->cmd);
		if (!access(cmd_path, F_OK))
		{
			cmd->path = cmd_path;
			return ;
		}
		else
			free(cmd_path);
		tmp_path++;
	}
	print_err("command not found", 127);
}

static void    set_fdtable(t_arg *arg)
{
        dup2(arg->input.fd, 0);
        dup2(arg->output.fd, 1);
}

void	set_arg(t_arg *arg, int argc, char **argv, char **path)
{
	char	**command1;
	char	**command2;

	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');
	arg->input.name = argv[1];
	arg->output.name = argv[argc - 1];
	arg->cmd1.cmd = ft_strjoin("/", command1[0]);
	arg->cmd1.opt = command1;
	arg->cmd2.cmd = ft_strjoin("/", command2[0]);
	arg->cmd2.opt = command2;
	set_fileinfo(arg);
	set_cmdinfo(&(arg->cmd1), path);
	set_cmdinfo(&(arg->cmd2), path);
	set_fdtable(arg);
}
