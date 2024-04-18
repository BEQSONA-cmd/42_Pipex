/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:12:09 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/18 12:26:32 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	ft_init_pipex(char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[4]) == 0 || argv[1] == NULL
		|| argv[4] == NULL)
		ft_error_exit(NULL, "Invalid file name\n", 1);
	if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
		ft_error_exit(NULL, "Invalid command\n", 1);
	pipex.file1 = ft_strdup(argv[1]);
	pipex.file2 = ft_strdup(argv[4]);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	pipex.path = ft_strdup(envp[i]);
	pipex.path1 = find_path(pipex.cmd1[0], pipex.path);
	pipex.path2 = find_path(pipex.cmd2[0], pipex.path);
	pipex.envp = envp;
	return (pipex);
}

void	ft_pipex(t_pipex *pipex)
{
	pid_t	pid;
	int		input;
	int		output;
	int		fd[2];

	if (pipex->cmd1[0] == NULL || pipex->cmd2[0] == NULL)
		ft_error_exit(NULL, "Invalid command\n", 1);
	input = open(pipex->file1, O_RDONLY, 0777);
	output = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipe(fd) == -1)
		ft_error_exit(NULL, "Pipe\n", 1);
	pid = fork();
	if (pid == 0)
		child_process1(pipex, pipex->path1, input, fd);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	child_process2(pipex, pipex->path2, output, fd);
	close(fd[0]);
	free(pipex->path1);
	free(pipex->path2);
}

void	child_process1(t_pipex *pipex, char *path1, int input, int *fd)
{
	if (input == -1)
		ft_error_exit(pipex->file1, ": No such file or directory\n", 1);
	if (path1 == NULL)
		ft_error_exit(pipex->cmd1[0], ": command not found\n", 127);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(input, STDIN_FILENO);
	close(input);
	execve(path1, pipex->cmd1, pipex->envp);
	ft_error_exit(NULL, "child1 fails\n", 1);
}

void	child_process2(t_pipex *pipex, char *path2, int output, int *fd)
{
	pid_t	pid2;

	if (output == -1)
		ft_error_exit(pipex->file2, ": No such file or directory\n", 1);
	if (path2 == NULL)
		ft_error_exit(pipex->cmd2[0], ": command not found\n", 127);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(output, STDOUT_FILENO);
		close(output);
		execve(path2, pipex->cmd2, pipex->envp);
		ft_error_exit(NULL, "child2 fails\n", 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_error_exit(NULL, "Invalid number of arguments\n", 1);
	pipex = ft_init_pipex(argv, envp);
	ft_pipex(&pipex);
	free_array(pipex.cmd1);
	free_array(pipex.cmd2);
	free(pipex.file1);
	free(pipex.file2);
	free(pipex.path);
	return (0);
}
