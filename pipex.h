/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:52 by btvildia          #+#    #+#             */
/*   Updated: 2024/03/28 18:07:46 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "src/ft_printf.h"
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

void		ft_no_file(char *arg);
void		free_array(char **arr);
void		ft_error(char *str);
void		print_array(char **arr, int j);

#endif
