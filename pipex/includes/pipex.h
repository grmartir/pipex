/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:49:39 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/07 20:49:41 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*cmd_path;
	char	**cmds;
	char	**cmd_args;
	char	*command;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
	int		here_doc;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
}			t_pipex;

int		main(int argc, char **argv, char **envp);
int		mandatory_main(int argc, char **argv, char **envp);
int		bonus_main(int argc, char *argv[], char *envp[]);
int		err(char *msg);
void	perror_error(char *msg);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
void	close_pipe(t_pipex *pipex);
char	*find_path(char **envp);
char	*get_cmd(char *cmd, char **paths);
void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);
void	pipe_free(t_pipex *pipex);
int		args_in(char *arg, t_pipex *pipex);
void	here_doc(char *argv, t_pipex *pipex);
void	sub_dup2(int zero, int first);
void	child(t_pipex p, char **argv, char **envp);
void	get_infile(char **argv, t_pipex *pipex);
void	get_outfile(char *argv, t_pipex *pipex);
void	creat_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	parent_free_bon(t_pipex *pipex);

#endif
