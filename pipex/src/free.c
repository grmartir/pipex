/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:50:19 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/07 20:50:20 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex -> infile);
	close(pipex -> outfile);
	while (pipex->cmds[i])
	{
		free(pipex->cmds[i]);
		i++;
	}
	free(pipex->cmds);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex ->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->command);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	pipe_free(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	free(pipex->pipe);
	err("Env error!");
	exit(1);
}

void	parent_free_bon(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex -> infile);
	close(pipex -> outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipe);
}
