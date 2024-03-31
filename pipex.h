/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:52 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/30 21:56:48 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*file1;
	char	*file2;
	char	*path;
}			t_pipex;

int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strncpy(char *s1, char *s2, int n);
int			ft_strlen(char *c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(char *s1);
char		**ft_split(char *s, char c);
void		ft_no_command(char *cmd);
void		ft_error(char *str);
void		ft_no_file(char *arg);
void		free_array(char **arr);
void		ft_error(char *str);
void		print_array(char **arr, int j);

#endif
