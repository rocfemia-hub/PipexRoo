/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:45:10 by roo               #+#    #+#             */
/*   Updated: 2025/05/11 03:51:26 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int args_control(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		return(free(pipex), ft_printf("Error de argumentos"), -1);
	pipex->infile = open(argv[1], O_RDONLY); //open devuelve el fd en el q estamos
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644); //si no existe lo crea, abre en modo escritura, si existe lo borra y empieza vacío, permisos de rw-r--r--.
	if (pipex->infile < 0 || pipex->outfile < 0)
		return(free(pipex), ft_printf("Error de apertura de archivo"), -1);
	pipex->cmd1 = ft_split(argv[2], ' '); // lo spliteamos porque la función execve recibe los argumentos separados {"ls", "-la"}
	pipex->cmd2 = ft_split(argv[3], ' ');
	return (0);
}

char *get_path(char *cmd, char **envp) //algún leack por no comprobar si el envp existe?
{
	int i;
	char *paths_str;
	char **paths;
	
	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	paths_str = envp[i] + 5;
	paths = ft_split(paths_str, ':');
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->envp = envp;
	if(args_control(argc, argv, pipex) != 0)
		return(0);
}