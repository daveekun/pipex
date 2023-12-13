/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/13 18:24:30 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int get_fds(int i, char **argv, int argc, int fd[2], int *prev_out)
{
	int pipefd[2];

	if (i == argc - 4)
	{
		fd[1] = open(argv[argc - 1],  O_TRUNC | O_WRONLY | O_CREAT, 0644);
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

int print_usage(void)
{
	ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	return (0);
}

int main(int argc, char **argv, char **env)
{
	int i;
	int	fds[2];
	int	prev_out;
	pid_t	*pids;
	t_command cmd;

	if (argc != 5)
		return (print_usage());
	pids = ft_calloc(argc - 2, sizeof(pid_t));
	prev_out = 0;
	cmd.env = env;
	i = 0;
	while (i < argc - 3)
	{
		cmd.params = arg_split(argv[i + 2], ' ');
		if (!cmd.params)
			return (print_error(cmd.params));
		if (get_fds(i, argv, argc, fds, &prev_out) == 1)
			return (print_error(cmd.params));
		call_command(fds, cmd, pids, i++);
		close(fds[1]);
		free_args(cmd.params);
	}
	close(prev_out);
	wait_for_commands(pids);
}

int print_error(char **params)
{
	free_args(params);
	perror("pipex");
	return (1);
}

void wait_for_commands(pid_t *pids)
{
	int i;
	int	status;
	int exit_status;

	i = 0;
	exit_status = 0;
	while (pids[i])
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status);
		i++;
	}
	free(pids);
	exit(exit_status);
}

void	call_command(int fds[2], t_command cmd, int *pids, int i)
{
	char *path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		path = find_command(cmd.params, cmd.env);
		if (!path)
		{
			ft_printf("command not found: %s\n", cmd.params[0]);
			exit(127);
		}
		dup2(fds[0], 0);
		dup2(fds[1], 1);
		execve(path, cmd.params, cmd.env);
	}
	else if (pid > 0)
	{
		if (!pids)
		{
			print_error(0);
			exit(0);
		}
		pids[i] = pid;
	}
}
