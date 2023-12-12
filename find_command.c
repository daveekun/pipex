/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:37:53 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/12 12:20:02 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i]);
		i++;
	}
	return (0);
}

static char **fix_path(char **locations)
{
	int	i;

	i = 0;
	while (locations && locations[i])
	{
		locations[i] = ft_strjoin(locations[i], "/");
		i++;
	}
	return (locations);
}

char *find_command(char **args, char **env)
{
	char	**locations;
	int		path_index;
	char	*c_path;
	const char	*path = get_path(env);

	locations = fix_path(ft_split(path, ':'));
	path_index = 0;
	while (locations && locations[path_index])
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
