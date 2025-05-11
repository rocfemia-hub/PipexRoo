/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roo <roo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:45:10 by roo               #+#    #+#             */
/*   Updated: 2025/05/11 21:32:35 by roo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int args_control(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		return(ft_printf("Error de argumentos"), -1);
	pipex->infile = open(argv[1], O_RDONLY); //open devuelve el fd en el q estamos
	pipex->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644); //si no existe lo crea, abre en modo escritura, si existe lo borra y empieza vacío, permisos de rw-r--r--.
	if (pipex->infile < 0 || pipex->outfile < 0)
		return(ft_printf("Error de apertura de archivo"), -1);
	pipex->cmd1 = ft_split(argv[2], ' '); //lo spliteamos porque la función execve recibe los argumentos separados {"ls", "-la"}
	pipex->cmd2 = ft_split(argv[3], ' ');
	return (0);
}

char *get_path(char *cmd, char **envp)
{
	int		i;
	char	*paths_str;
	char	**paths;
	char	*result;
	
	i = -1;
	while(envp[++i]) //algún leack por no comprobar si el envp existe?
		if(ft_strncmp(envp[i], "PATH=", 5) == 0) //si los 5 primeros carácteres son "PATH=" estamos donde queremos
			break;
	paths_str = &envp[i][5]; //posición de memoria del quinto caracter, saltándonos "PATH="
	paths = ft_split(paths_str, ':');
	i = 0;
	result = NULL;
	while(paths[i])
	{
		result = ft_strjoin(paths[i], "/"); //añadimos / al dinal del path
		result = ft_strjoin_gnl(result, cmd); //añadimos el comando que nos hayan mandado al final del path con el de gnl para evitar leack (libera result)
		if (access(result, X_OK) == 0)
 			break;
		free(result);
		i++;
	}
	return(ft_free_free(paths), result);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->envp = envp;
	if(args_control(argc, argv, pipex) != 0)
		return(free(pipex), 0);
	return(0);
}
