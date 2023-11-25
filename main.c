/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/25 16:56:48 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>

char *find_command(char **args);

int	main(int argc, char **argv)
{
	pid_t pid;
	pid_t second;
	int i;
	int pipefd[2];
	char	**params;
	char *const env[] = {NULL};
	char 	**second_params;
	char *const second_env[] = {NULL};
	char *path;
	char *second_path;

	if (argc != 5)
	{
		ft_printf("invalid input: Usage ./pipex infile cmd1 cmd2 outfile\n");
		return (0);
	}
	params = ft_split(argv[2], ' ');
	if (!params)
	{
		ft_printf("malloc failed in ft_split\n");
		return (0);
	}
	second_params = ft_split(argv[3], ' ');
	if (!second_params)
	{
		i = 0;
		ft_printf("malloc failed in ft_split\n");
		while (params[i])
				free(params[i++]);
		free(params);
		return (0);
	}
	if (pipe(pipefd) != 0)
	{
		ft_printf("failed to set up pipe\n");
		i = 0;
		while (params[i])
				free(params[i++]);
		free(params);
		i = 0;
		while (second_params[i])
				free(second_params[i++]);
		free(second_params);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		int input = open(argv[1], O_RDONLY);
		if (input == -1)
		{
			ft_printf("failed to open input file\n");
			i = 0;
			while (params[i])
					free(params[i++]);
			free(params);
			i = 0;
			while (second_params[i])
				free(second_params[i++]);
			free(second_params);
			close(pipefd[0]);
			close(pipefd[1]);
			return (0);
		}
		dup2(input, 0);
		dup2(pipefd[1], 1);
		path = find_command(params);
		if (path)
			execve(path, params, env);
		else
			ft_printf("command not found or error occured\n");
		close(input);
		exit(0);
	}
	else if (pid < 0)
	{
		second = fork();
		if (second == 0)
		{
			close(pipefd[1]);
			int out = open(argv[4], O_RDWR);
			if (out == -1)
			{
				ft_printf("failed to open output file\n");
				i = 0;
				while (params[i])
						free(params[i++]);
				free(params);
				i = 0;
				while (second_params[i])
						free(second_params[i++]);
				free(second_params);
				close(pipefd[0]);
				return (0);
			}
			dup2(pipefd[0], 0);
			dup2(out, 1);
			second_path = find_command(second_params);
			if (second_path)
				execve(second_path, second_params, second_env);
			else
				ft_printf("command not found or malloc issue\n");
			close(out);
			exit(0);
		}
		else if (pid == -1)
		{
			ft_printf("fork failed to create child process\n");
			i = 0;
			while (params[i])
					free(params[i++]);
			free(params);
			i = 0;
			while (second_params[i])
					free(second_params[i++]);
			free(second_params);
			close(pipefd[0]);
			close(pipefd[1]);
			return (0);
		}
	}
	else
	{
		ft_printf("fork failed to create child process\n");
		i = 0;
		while (params[i])
				free(params[i++]);
		free(params);
		i = 0;
		while (second_params[i])
				free(second_params[i++]);
		free(second_params);
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
}

char *find_command(char **args)
{
	char **locations;
	int path_index;
	char	*c_path;

	locations = ft_split("/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/", ':');
	path_index = 0;
	while (locations[path_index])
	{
		c_path = ft_strjoin(locations[path_index], args[0]);
		if (!c_path)
			return (0);
		if (access(c_path, F_OK) == 0)
		{
			path_index = 0;
			while (locations[path_index])
				free(locations[path_index++]);
			free(locations);
			return (c_path);
		}
		else
			free(c_path);
		path_index++;
	}
	return (0);
}
