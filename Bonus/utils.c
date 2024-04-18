/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:42 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/18 21:08:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	return (file);
}

void	here_doc(char *limiter)
{
	int		pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_error_exit("Pipe error\n", NULL, 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& ft_strlen(line) - 1 == ft_strlen(limiter))
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, NULL, 0);
}

void	ft_execve(char *argv, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

	i = 0;
	cmd = ft_split(argv, ' ');
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = find_path(cmd[0], envp[i]);
	i = 0;
	if (!path)
		ft_error_exit(argv, ": command not found\n", 127);
	if (execve(path, cmd, envp) == -1)
		ft_error_exit(NULL, "child1 fails\n", 1);
}
