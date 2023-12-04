/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:50:26 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/07 20:50:28 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	open_files(t_pipex *pipex, char **argv, int argc)
{
	pipex -> infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror_error("Cant open argv[1]\n");
	pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0000644);
	if (pipex -> outfile == -1)
		perror_error("Cant open argv[argc -1]\n");
}

int	mandatory_main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		return (err("Incorrect number of args\n"));
	open_files(&pipex, argv, argc);
	if (pipe(pipex.fd) == -1)
		perror_error("Pipex error\n");
	pipex.cmd_path = find_path(envp);
	pipex.cmds = ft_split(pipex.cmd_path, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		perror_error("Fork error\n");
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		perror_error("Fork error\n");
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipe(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		bonus_main(argc, argv, envp);
	else
		mandatory_main(argc, argv, envp);
}
