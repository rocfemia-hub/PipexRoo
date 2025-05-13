/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:45:10 by roo               #+#    #+#             */
/*   Updated: 2025/05/13 21:16:00 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	args_control(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		return (ft_printf("Error de argumentos\n"), -1);
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
		return (ft_printf("Error de apertura de archivo\n"), -1);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	return (0);
}

char	*get_path(char *cmd, char **envp, t_pipex *pipex)
{
	char	*paths_str;
	char	**paths;
	char	*result;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	pipex->i = -1;
	while (envp[++pipex->i])
		if (ft_strncmp(envp[pipex->i], "PATH=", 5) == 0)
			break ;
	paths_str = &envp[pipex->i][5];
	paths = ft_split(paths_str, ':');
	pipex->i = -1;
	while (paths[++pipex->i])
	{
		result = ft_strjoin(paths[pipex->i], "/");
		result = ft_strjoin_gnl(result, cmd);
		if (access(result, X_OK) == 0)
			break ;
		free(result);
		result = NULL;
	}
	if (result == NULL)
		return (result);
	return (ft_free_free(paths), result);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->envp = envp;
	if (args_control(argc, argv, pipex) != 0)
		return (finish(pipex), 0);
	pipex->path_cmd1 = get_path(pipex->cmd1[0], pipex->envp, pipex);
	pipex->path_cmd2 = get_path(pipex->cmd2[0], pipex->envp, pipex);
	execute(pipex);
	return (finish(pipex), 0);
}
