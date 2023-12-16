/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:29:24 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/16 17:37:35 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_command
{
	char	**params;
	char	**env;
	char	*path;
}	t_command;

typedef struct s_args
{
	int		c;
	char	**v;
}	t_args;

char	*find_command(char **args, char **env);
void	call_command(int fds[2], t_command cmd, int *pids, int i);
void	wait_for_commands(pid_t *pids);
int		print_error(char **params);
char	**arg_split(char *s, char c);
void	free_args(char **s);
int		open_if_fail(char *path, int ret);
int		get_fds(int i, t_args args, int fd[2], int *prev_out);
void	free_args(char **s);
int		print_usage(void);
int		print_error(char **params);

#endif
