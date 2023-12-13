/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:29:24 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/13 13:52:12 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_command
{
	char		**params;
	char 		**env;
	char 		*path;
}	t_command;

char	*find_command(char **args, char **env);
void	call_command(int fds[2], t_command cmd, int *pids, int i);
void	wait_for_commands(pid_t *pids);
int		print_error(char **params);
char	**arg_split(char *s, char c);
void	free_args(char **s);
#endif
