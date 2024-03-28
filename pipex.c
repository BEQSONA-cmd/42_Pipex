/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:12:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/28 18:09:30 by btvildia         ###   ########.fr       */
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

void	ft_pipex(t_pipex *pipex, char **envp)
{
	pid_t	pid;
	char	*path1;
	char	*path2;
	int		input;
	int		output;
	int		fd[2];

	// print_array(pipex->cmd1, 0);
	// print_array(pipex->cmd2, 1);
	path1 = find_path(pipex->cmd1[0], pipex->path);
	path2 = find_path(pipex->cmd2[0], pipex->path);
	input = open(pipex->file1, O_RDONLY, 0777);
	output = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe(fd) == -1)
		ft_error("Pipe\n");
	pid = fork();
	if (pid == 0)
	{
		if (input == -1)
			ft_no_file(pipex->file1);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(input, STDIN_FILENO);
		close(input);
		execve(path1, pipex->cmd1, envp);
		perror("Command 1");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(output, STDOUT_FILENO);
		close(output);
		execve(path2, pipex->cmd2, envp);
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
		ft_pipex(&pipex, envp);
	}
	return (0);
}
