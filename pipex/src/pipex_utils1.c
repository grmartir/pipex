/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 23:55:10 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/10 23:55:12 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], pipex);
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			perror_error("Infile error!");
	}
}

void	get_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->outfile < 0)
		perror_error("Outfile error!");
}

void	creat_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			parent_free_bon(pipex);
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nmbs))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

int	bonus_main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc < args_in(argv[1], &pipex))
		return (err("Input error!"));
	get_infile(argv, &pipex);
	get_outfile(argv[argc - 1], &pipex);
	pipex.cmd_nmbs = argc - 3 - pipex.here_doc;
	pipex.pipe_nmbs = 2 * (pipex.cmd_nmbs - 1);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_nmbs);
	if (!pipex.pipe)
		perror_error("Pipe error!");
	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	if (!pipex.cmd_paths)
		pipe_free(&pipex);
	creat_pipes(&pipex);
	pipex.idx = -1;
	while (++(pipex.idx) < pipex.cmd_nmbs)
		child(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	parent_free_bon(&pipex);
	return (0);
}
