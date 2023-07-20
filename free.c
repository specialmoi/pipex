/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthiruma <pthiruma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:43:31 by pthiruma          #+#    #+#             */
/*   Updated: 2023/06/23 13:18:05 by pthiruma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close((*pipex).infile_fd);
	close((*pipex).outfile_fd);
	while ((*pipex).cmd_paths[i])
	{
		free((*pipex).cmd_paths[i]);
		i++;
	}
	free((*pipex).cmd_paths);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while ((*pipex).cmd_args[i])
	{
		free((*pipex).cmd_args[i]);
		i++;
	}
	free((*pipex).cmd_args);
	free((*pipex).cmd);
	
	i = 0;
	close((*pipex).infile_fd);
	close((*pipex).outfile_fd);
	while ((*pipex).cmd_paths[i])
	{
		free((*pipex).cmd_paths[i]);
		i++;
	}
	free((*pipex).cmd_paths);
}
