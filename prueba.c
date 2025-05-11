/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:31:28 by roo               #+#    #+#             */
/*   Updated: 2025/04/27 21:48:45 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	int fd1[2];
	int fd2[2];
	int status;
	int pid;

	pipe(fd1);
	
	pid = fork(); //hijo 1

	if(pid == 0) //es el hijo 1
	{
		close(fd1[READ_FD]); //tienes q estar cerrando todo el rato!
		
		dup2(fd1[WRITE_FD], STDOUT_FILENO);
		close(fd1[WRITE_FD]);
		
		execlp("/usr/bin/ls", "ls", "-l", NULL);
	}
	else //es el padre
	{
		close(fd1[WRITE_FD]);
		
		pipe(fd2);
		
		pid = fork(); //hijo 2
		
		if(pid == 0) //es el hijo 2
		{
			close(fd2[READ_FD]); //siempre cerramos los extremos no necesarios o que ya no estemos usando
			
			dup2(fd1[READ_FD], STDIN_FILENO);
			close(fd1[READ_FD]);

			dup2(fd2[WRITE_FD], STDOUT_FILENO);
			close(fd2[WRITE_FD]);
			
			execlp("/usr/bin/grep", "grep", "u", NULL);
		}
		else //es el padre
		{
			close(fd1[READ_FD]);
			close(fd2[WRITE_FD]);

			pid = fork(); //hijo 3
			
			if(pid == 0) //es el hijo 3
			{
				dup2(fd2[READ_FD], STDIN_FILENO);
				close(fd2[READ_FD]);

				execlp("/usr/bin/wc", "wc", "-l", NULL);
			}
		}
	}
	close(fd2[READ_FD]);
	wait(&status);
	wait(&status);
	wait(&status);
	return(0);
}
