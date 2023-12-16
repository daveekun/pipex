/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/16 17:37:58 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	main(int argc, char **argv, char **env)
{
	int			i;
	int			fds[2];
	int			prev_out;
	pid_t		*pids;
	t_command	cmd;

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
		if (get_fds(i, (t_args){argc, argv}, fds, &prev_out) == 1)
			return (print_error(cmd.params));
		call_command(fds, cmd, pids, i++);
		close(fds[1]);
		free_args(cmd.params);
	}
	close(prev_out);
	wait_for_commands(pids);
}
