/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:06:44 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/06 14:06:58 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env);

int	main(int argc, char **argv, char **env)
{
	pid_t pid;
	int pipefd[2];
	char	*path;

	if (argc != 5)
		return(error_return(0));
	path = get_path(env);
	if (!path)
		return(error_return(0));
	if (pipe(pipefd) != 0)
		return(error_return(0));
	pid = fork();
	if (pid == 0)
	{
		if (!input_function(pipefd, argv[1], pid, (t_command){.params = ft_split(argv[2], ' '), .env = env, .path = path}))
			return(error_return(0));
	}
	else if (pid > 0)
	{
		if (!output_function(pipefd, argv[4], fork(), (t_command){.params = ft_split(argv[3], ' '), .env = env, .path = path}))
			return(error_return(0));
	}
	else
		return(error_return(0));
}

char	*get_path(char **env)
{
	(void)env;
	return ("Users/dhorvath/lbin/bin/:/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/");
}