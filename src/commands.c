/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:22:27 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/16 16:53:12 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

void	wait_for_commands(pid_t *pids)
{
	int	i;
	int	status;
	int	exit_status;

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
	char	*path;
	pid_t	pid;

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
