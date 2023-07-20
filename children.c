/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthiruma <pthiruma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 23:00:27 by pthiruma          #+#    #+#             */
/*   Updated: 2023/06/23 13:27:56 by pthiruma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **cmd_paths, char *cmd_args)
{
	char	*tmp;
	char	*cmd;
	int		i;

	i = 0;
	if (!cmd_args)
		return (NULL);
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		cmd = ft_strjoin(tmp, cmd_args);
		free(tmp);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.infile_fd, STDIN_FILENO);
	close(pipex.tube[0]);
	dup2(pipex.tube[1], STDOUT_FILENO);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (access(argv[2], X_OK) == 0)
		pipex.cmd = argv[2];
	else
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit (1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.outfile_fd, STDOUT_FILENO);
	close(pipex.tube[1]);
	dup2(pipex.tube[0], STDIN_FILENO);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (access(argv[3], X_OK) == 0)
		pipex.cmd = argv[3];
	else
		pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
