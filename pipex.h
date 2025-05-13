/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:40:44 by roo               #+#    #+#             */
/*   Updated: 2025/05/13 21:03:58 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_FD 0
# define WRITE_FD 1

# include "./Helicopter/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct pipex
{
	int i;
	int	infile;
	int	outfile;
	char **envp;
	char **cmd1;
	char **cmd2;
	char *path_cmd1;
	char *path_cmd2;
}	t_pipex;


int		args_control(int argc, char **argv, t_pipex *pipex);
char	*get_path(char *cmd, char **envp, t_pipex *pipex);

int		execute(t_pipex *pipex);
int		execute2(int fd[2], t_pipex *pipex, int pid1);

void	close_all(int fd[2], t_pipex *pipex);
void	finish(t_pipex *pipex);

#endif