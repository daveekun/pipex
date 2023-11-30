/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/30 20:39:05 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	pid_t pid;
	int pipefd[2];

	if (argc != 5)
		return(error_return(0));
	if (pipe(pipefd) != 0)
		return(error_return(0));
	pid = fork();
	if (pid == 0)
	{
		if (!input_function(pipefd, argv[1], pid, (t_command){.params = ft_split(argv[2], ' '), .env = {NULL}}))
			return(error_return(0));
	}
	else if (pid > 0)
	{
		if (!output_function(pipefd, argv[4], fork(), (t_command){.params = ft_split(argv[3], ' '), .env = {NULL}}))
			return(error_return(0));
	}
	else
		return(error_return(0));
}
