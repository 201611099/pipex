/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:46:38 by hyojlee           #+#    #+#             */
/*   Updated: 2021/06/30 15:50:11 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", ft_strlen(*env)))
			return (*env + 5);
		(*env)++;
	}
	if (!*env)
	{
		perror("PATH");
		exit(1);
	}
	return (0);
}

int			main(int argc, char **argv, char **env)
{
	char	*path;

	if (!argc)
	{
		printf("%s", argv[1]);
	}
	path = get_env_path(env);
	printf("%s\n", path);
	return (0);
}
