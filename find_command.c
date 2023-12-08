/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:37:53 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/08 17:22:13 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return ("Users/dhorvath/lbin/bin/:/usr/local/bin/:/usr/bin/:/bin/:/usr/sbin/:/sbin/:/usr/local/munki/");
}

char *find_command(char **args, char **env)
{
	char	**locations;
	int		path_index;
	char	*c_path;
	const char	*path = get_path(env);

	locations = ft_split(path, ':');
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
