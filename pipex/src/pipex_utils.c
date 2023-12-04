/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:50:33 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/07 20:50:34 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd(char *cmd, char **paths)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.command = get_cmd(pipex.cmd_args[0], pipex.cmds);
	if (!pipex.command)
	{
		child_free(&pipex);
		err("First command not found");
		exit(1);
	}
	execve(pipex.command, pipex.cmd_args, envp);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.command = get_cmd(pipex.cmd_args[0], pipex.cmds);
	if (!pipex.command)
	{
		child_free(&pipex);
		err("Second command not found");
		exit(1);
	}
	execve(pipex.command, pipex.cmd_args, envp);
}

void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		p.cmd_args = ft_split(argv[2 + p.here_doc + p.idx], ' ');
		p.cmd = get_cmd(p.cmd_args[0], p.cmd_paths);
		if (!p.cmd)
		{
			write (2, "Error!", 6);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.cmd_args, envp);
	}
}
