/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:19:04 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/17 13:32:51 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_fds(int i, t_args args, int fd[2], int *prev_out)
{
	int	pipefd[2];

	if (i == args.c - 4)
	{
		fd[1] = open(args.v[args.c - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (fd[1] == -1)
			return (1);
		fd[0] = *prev_out;
	}
	else
	{
		if (pipe(pipefd) == -1)
			return (1);
		fd[0] = *prev_out;
		fd[1] = pipefd[1];
		*prev_out = pipefd[0];
	}
	if (i == 0)
	{
		fd[0] = open(args.v[1], O_RDONLY);
		if (fd[0] == -1)
			return (1);
	}
	return (0);
}
