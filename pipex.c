/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:12:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/31 21:57:19 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	ft_init_pipex(char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[4]) == 0 || argv[1] == NULL
		|| argv[4] == NULL)
		ft_error("Invalid file name\n");
	if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
		ft_error("Invalid command\n");
	pipex.file1 = ft_strdup(argv[1]);
	pipex.file2 = ft_strdup(argv[4]);
	pipex.cmd1 = NULL;
	pipex.cmd2 = NULL;
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
	if (paths[0] == NULL)
		ft_error("Invalid path\n");
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			free_array(paths);
			return (c);
		}
		free(c);
		i++;
	}
	free_array(paths);
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
	pid_t	pid2;

	path1 = find_path(pipex->cmd1[0], pipex->path);
	path2 = find_path(pipex->cmd2[0], pipex->path);
	if (pipex->cmd1[0] == NULL || pipex->cmd2[0] == NULL)
		ft_error("Invalid command\n");
	input = open(pipex->file1, O_RDONLY, 0777);
	output = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe(fd) == -1)
		ft_error("Pipe\n");
	pid = fork();
	if (pid == 0)
	{
		if (input == -1)
			ft_no_file(pipex->file1);
		if (path1 == NULL)
			ft_no_command(pipex->cmd1[0]);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		dup2(input, STDIN_FILENO);
		close(input);
		execve(path1, pipex->cmd1, envp);
		ft_error("child1 fails\n");
	}
	waitpid(pid, NULL, 0);
	if (output == -1)
		ft_no_file(pipex->file2);
	if (path2 == NULL)
		ft_no_command(pipex->cmd2[0]);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(output, STDOUT_FILENO);
		close(output);
		execve(path2, pipex->cmd2, envp);
		ft_error("child2 fails\n");
	}
	free(path1);
	free(path2);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error("Invalid number of arguments\n");
	pipex = ft_init_pipex(argv, envp);
	ft_pipex(&pipex, envp);
	free_array(pipex.cmd1);
	free_array(pipex.cmd2);
	free(pipex.file1);
	free(pipex.file2);
	free(pipex.path);
	return (0);
}
