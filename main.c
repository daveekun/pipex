/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/24 18:02:57 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	pid_t pid;
	pid_t second;
	int pipefd[2];
	char *const params[] = {"grep", "ass", NULL};
	char *const env[] = {NULL};
	char *const wc_params[] = {"wc", "-c", NULL};
	char *const wc_env[] = {NULL};

	if (argc != 3)
	{
		return (0);
	}
	pipe(pipefd);
	pid = fork();
	/* child process */
	if (pid == 0)
	{
		int input = open(argv[1], O_RDONLY);
		dup2(input, 0);
		dup2(pipefd[1], 1);
		execve("/usr/bin/grep", params, env);
		exit(0);
	}
	else if (pid == -1)
	{
		ft_printf("Process failed, way to go stupid\n");
	}
	/* parent process */
	else
	{
		/* 2nd child process */
		second = fork();
		if (second == 0)
		{
			close(pipefd[1]);
			int out = open(argv[2], O_RDWR);
			dup2(pipefd[0], 0);
			dup2(out, 1);
			execve("/usr/bin/wc", wc_params, wc_env);
			exit(0);
		}
	}
}
