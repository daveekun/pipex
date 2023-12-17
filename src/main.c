/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/17 15:25:33 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	close_fds(int fds[2])
{
	close(fds[1]);
	close(fds[0]);
}

int	main(int argc, char **argv, char **env)
{
	int			i;
	int			fds[2];
	int			prev_out;
	pid_t		*pids;
	char		**params;

	if (argc != 5)
		return (print_usage());
	pids = ft_calloc(argc - 2, sizeof(pid_t));
	prev_out = 0;
	i = 0;
	while (i < argc - 3)
	{
		params = arg_split(argv[i + 2], ' ');
		if (!params)
			return (print_error(params));
		if (get_fds(i++, (t_args){argc, argv}, fds, &prev_out) == 1)
			print_error(0);
		else
			call_command(fds, (t_command){params, env, 0}, pids, i - 1);
		close_fds(fds);
		free_args(params);
	}
	close(prev_out);
	wait_for_commands(pids);
}
