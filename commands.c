/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:37:19 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/30 20:37:39 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	output_function(int pipefd[2], char *outfile, int pid, t_command cmd)
{
	char	*path;
	int		out;

	if (!cmd.params)
		return(error_return(0));
	if (pid == 0)
	{
		out = open(outfile, O_RDWR);
		if (out == -1)
			return(error_return(0));
		dup2(pipefd[0], 0);
		dup2(out, 1);
		path = find_command(cmd.params);
		if (path)
			execve(path, cmd.params, cmd.env);
		else
			return (0);
		close(out);
		exit(0);
		return (1);
	}
	return (0);
}

int	input_function(int pipefd[2], char *infile, int pid, t_command cmd)
{
	char	*path;
	int		inp;

	if (!cmd.params)
		return(error_return(0));
	if (pid == 0)
	{
	 	inp = open(infile, O_RDONLY);
		if (inp == -1)
			return(error_return(0));
		dup2(inp, 0);
		dup2(pipefd[1], 1);
		path = find_command(cmd.params[0]);
		if (path)
			execve(path, cmd.params, cmd.env);
		else
			return(error_return(0));
		close(inp);
		exit(0);
	}
}