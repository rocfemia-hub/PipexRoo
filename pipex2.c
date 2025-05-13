/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 04:52:40 by roo               #+#    #+#             */
/*   Updated: 2025/05/13 21:17:28 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(t_pipex *pipex)
{
	int	fd[2];
	int	pid1;

	if (pipe(fd) == -1)
		return (ft_printf("Error de creación de pipe\n"), -1);
	if (pipex->path_cmd1 == NULL)
		return (ft_printf("Comand not found\n"), execute2(fd, pipex, -1), -1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(fd[WRITE_FD], STDOUT_FILENO);
		close_all(fd, pipex);
		if (execve(pipex->path_cmd1, pipex->cmd1, pipex->envp) == -1)
			return (ft_printf("Error de ejecución\n"), -1);
	}
	else
	{
		if (execute2(fd, pipex, pid1) == -1)
			return (-1);
	}
	return (0);
}

int	execute2(int fd[2], t_pipex *pipex, int pid1)
{
	int	pid2;

	if (pipex->path_cmd2 == NULL)
		return (ft_printf("Comando no encontrado\n"), -1);
	pid2 = fork();
	if (pid2 == 0)
	{
		if (pipex->path_cmd1)
			dup2(fd[READ_FD], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close_all(fd, pipex);
		if (execve(pipex->path_cmd2, pipex->cmd2, pipex->envp) == -1)
			return (ft_printf("Error de ejecución\n"), -1);
	}
	else
	{
		close_all(fd, pipex);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		return (0);
	}
	return (0);
}

void	close_all(int fd[2], t_pipex *pipex)
{
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	close(pipex->infile);
	close(pipex->outfile);
}

void	finish(t_pipex *pipex)
{
	if (pipex->path_cmd1)
		free(pipex->path_cmd1);
	if (pipex->path_cmd2)
		free(pipex->path_cmd2);
	ft_free_free(pipex->cmd1);
	ft_free_free(pipex->cmd2);
	free(pipex);
}

//intentar romper proyecto y arreglar seg f.