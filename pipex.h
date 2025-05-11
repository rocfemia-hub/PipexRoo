/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:40:44 by roo               #+#    #+#             */
/*   Updated: 2025/05/11 21:27:43 by roo              ###   ########.fr       */
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
	int	infile;
	int	outfile;
	char **envp;
	char **cmd1;
	char **cmd2;
}	t_pipex;


int		args_control(int argc, char **argv, t_pipex *pipex);
char	*get_path(char *cmd, char **envp);

#endif