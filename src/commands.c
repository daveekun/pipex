/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:22:27 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/17 15:18:16 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"
#include "libft.h"

void	wait_for_commands(pid_t *pids)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (pids && pids[i])
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (exit_status == -1)
			break ;
		i++;
	}
	free(pids);
	exit(exit_status);
}

int	child_error(void)
{
	print_error(0);
	exit(-1);
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
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putendl_fd(cmd.params[0], 2);
			exit(127);
		}
		if (dup2(fds[0], 0) == -1 || dup2(fds[1], 1) == -1)
			child_error();
		execve(path, cmd.params, cmd.env);
	}
	else if (pid > 0)
	{
		if (!pids)
			child_error();
		pids[i] = pid;
	}
	else
		child_error();
}
