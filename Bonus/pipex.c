/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:10 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/18 21:18:21 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	ft_init_pipex_bonus(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 2;
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[argc - 1]) == 0
		|| argv[1] == NULL || argv[argc - 1] == NULL)
		ft_error_exit(NULL, "Invalid file name\n", 1);
	while (i < argc - 2)
	{
		if (ft_strlen(argv[i]) == 0 || argv[i] == NULL)
			ft_error_exit(NULL, "Invalid command\n", 1);
		i++;
	}
	pipex.file1 = ft_strdup(argv[1]);
	pipex.file2 = ft_strdup(argv[argc - 1]);
	pipex.infile = open_file(pipex.file1, 2);
	pipex.outfile = open_file(pipex.file2, 1);
	pipex.envp = envp;
	return (pipex);
}

void	child_process(char *argv, char **envp, int filein, char *file1)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error_exit("Pipe error\n", NULL, 1);
	pid = fork();
	if (pid == -1)
		ft_error_exit("Fork error\n", NULL, 1);
	if (pid == 0)
	{
		if (filein == -1)
			ft_error_exit(file1, ": No such file or directory\n", 1);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_execve(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 2;
	if (argc < 5 || ((ft_strncmp(argv[1], "here_doc", 8) == 0) && argc < 6))
		ft_error_exit(NULL, "Invalid number of arguments\n", 1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex.outfile = open_file(argv[argc - 1], 0);
		here_doc(argv[2]);
	}
	else
	{
		pipex = ft_init_pipex_bonus(argc, argv, envp);
		dup2(pipex.infile, STDIN_FILENO);
		while (i < argc - 2)
		{
			child_process(argv[i], envp, pipex.infile, pipex.file1);
			i++;
		}
	}
	dup2(pipex.outfile, STDOUT_FILENO);
	ft_execve(argv[argc - 2], envp);
	return (0);
}
