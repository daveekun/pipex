/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/10 15:24:27 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int print_error(void);

int get_fds(int i, char **argv, int argc, int fd[2], int *prev_out)
{
	int pipefd[2];

	if (i == argc - 4)
	{
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT);
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
		fd[0] = open(argv[1], O_RDONLY);
		if (fd[0] == -1)
			return (1);
	}
	return (0);
}

void free_args(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

int main(int argc, char **argv, char **env)
{
	int i;
	int	fds[2];
	int	prev_out;
	pid_t	*pids;
	t_command cmd;

	if (argc != 5)
		return (print_error());
	pids = ft_calloc(argc - 2, sizeof(pid_t));
	prev_out = 0;
	cmd.env = env;
	i = 0;
	while (i < argc - 3)
	{
		cmd.params = ft_split(argv[i + 2], ' ');
		if (!cmd.params)
			return (print_error());
		if (get_fds(i, argv, argc, fds, &prev_out) == 1)
			return (print_error());
		call_command(fds, cmd, pids, i++);
		free_args(cmd.params);
	}
	close(prev_out);
	wait_for_commands(pids, i);
}

int print_error(void)
{
	perror("An error occured");
	return (1);
}

void wait_for_commands(pid_t *pids, int max)
{
	int i;
	int	*status;

	status = ft_calloc(max + 1, sizeof(int));
	if (!status)
		return (print_error());
	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &status[i], 1);
		i++;
	}
	free(pids);
	free(status);
	exit(0);
}

void	call_command(int fds[2], t_command cmd, int *pids, int i)
{
	char *path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_command(cmd.params, cmd.env);
		dup2(fds[0], 0);
		dup2(fds[1], 1);
		execve(path, cmd.params, cmd.env);
		close(fds[0]);
		exit(0);
	}
	else if (pid > 0)
	{
		if (!pids)
		{
			print_error();
			exit(0);
		}
		pids[i] = pid;
	}
}
