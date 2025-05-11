/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:40:44 by roo               #+#    #+#             */
/*   Updated: 2025/05/10 04:34:26 by roo              ###   ########.fr       */
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

#endif