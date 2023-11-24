/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/24 15:40:28 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "ft_printf.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	pid_t pid;
	int pipefd[2];
	char *const params[] = {"ls", "-a", "/Users/dhorvath", NULL};
	char *const env[] = {NULL};

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);

		dup2(pipefd[1], 1);
		execve("/bin/ls", params, env);
		exit(1);
	}
	else if (pid == -1)
	{
		ft_printf("Process failed, way to go stupid\n");
	}
	else
	{
		char buf[1];
		int fd = open("outfile", O_WRONLY);
		
		while (read(pipefd[0], buf, 1))
		{
			write(fd, buf, 1);
		}
		ft_printf("master\n");
		exit(1);
	}
}
