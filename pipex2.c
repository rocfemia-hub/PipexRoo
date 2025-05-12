/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:52:40 by roo               #+#    #+#             */
/*   Updated: 2025/05/12 06:39:10 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int execute(t_pipex *pipex)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if(pipe(fd) == -1)
		return(ft_printf("Error de no tengo muy claro el que"), -1); //q pongo aqui?
	pid1 = fork();
	if(pid1 == 0)
	{
		close(fd[READ_FD]); //Cambia los [READ_FD] y [WRITE_FD] por [0] y [1]
		dup2(pipex->infile, STDIN_FILENO);
		dup2(fd[WRITE_FD], STDOUT_FILENO);
		close(fd[WRITE_FD]);
		execve(get_path(pipex->cmd1[0], pipex->envp), pipex->cmd1, pipex->envp);
	}
	pid2 = fork();
	if(pid2 == 0)
	{
		close(fd[WRITE_FD]); //Sigo sin entender muy bien cuando hay que poner [READ_FD] y [WRITE_FD]
		dup2(fd[READ_FD], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(fd[READ_FD]);
		execve(get_path(pipex->cmd2[0], pipex->envp), pipex->cmd2, pipex->envp);
	}
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	wait(); //q coño hago aqui?
	wait(); //como funciona wait??
	return(0);
}
