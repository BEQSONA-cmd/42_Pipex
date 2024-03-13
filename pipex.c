/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:12:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/13 18:40:48 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	ft_init_pipex(char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	pipex.file1 = ft_strdup(argv[1]);
	pipex.file2 = ft_strdup(argv[4]);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	// while (pipex.cmd1[i])
	// {
	// 	ft_printf("cmd1[%d] = %s\n", i, pipex.cmd1[i]);
	// 	i++;
	// }
	// i = 0;
	// while (pipex.cmd2[i])
	// {
	// 	ft_printf("cmd2[%d] = %s\n", i, pipex.cmd2[i]);
	// 	i++;
	// }
	// i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	pipex.path = ft_strdup(envp[i]);
	return (pipex);
}

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (c);
		}
		i++;
	}
	ft_error("Command not found\n");
	return (NULL);
}

void	ft_pipex(t_pipex *pipex)
{
	int		fd[2];
	pid_t	pid;
	char	*path1;
	char	*path2;

	path1 = find_path(pipex->cmd1[0], pipex->path);
	path2 = find_path(pipex->cmd2[0], pipex->path);
	if (pipe(fd) == -1)
		ft_error("Pipe\n");
	pid = fork();
	if (pid == -1)
		ft_error("Fork\n");
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path1, pipex->cmd1, NULL);
		perror("Command 1");
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path2, pipex->cmd2, NULL);
		perror("Command 2");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error("Invalid number of arguments\n");
	else
	{
		pipex = ft_init_pipex(argv, envp);
		ft_pipex(&pipex);
	}
	return (0);
}
