/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:37:53 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/16 16:53:38 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static char	*free_and_null(char **locations);
static char	*free_and_null_end(char **locations, char **args);

static char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			if (env[i][5] == '\0')
				return (0);
			return (env[i]);
		}
		i++;
	}
	return (0);
}

static char	**fix_path(char **locations)
{
	int		i;
	char	*temp;

	i = 0;
	if (!locations)
		return (0);
	while (locations && locations[i])
	{
		temp = locations[i];
		locations[i] = ft_strjoin(locations[i], "/");
		if (!locations[i])
		{
			locations[i] = temp;
			i = 0;
			while (locations[i])
				free(locations[i++]);
			free(locations);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (locations);
}

static char	*free_and_null(char **locations)
{
	int	path_index;

	path_index = 0;
	while (locations && locations[path_index])
		free((void *)locations[path_index++]);
	free((void *)locations);
	return (0);
}

static char	*free_and_null_end(char **locations, char **args)
{
	int	path_index;

	path_index = 0;
	while (locations && locations[path_index])
		free((void *)locations[path_index++]);
	free((void *)locations);
	if (access(args[0], F_OK) == 0)
		return (args[0]);
	return (0);
}

char	*find_command(char **args, char **env)
{
	int			path_index;
	char		*c_path;
	const char	*path = get_path(env);
	const char	**locations = (const char **)fix_path(ft_split(path, ':'));

	path_index = 0;
	while (locations && locations[path_index])
	{
		c_path = ft_strjoin(locations[path_index], args[0]);
		if (!c_path)
			return (free_and_null((char **)locations));
		if (access(c_path, F_OK) == 0)
		{
			path_index = 0;
			while (locations[path_index])
				free((void *)locations[path_index++]);
			free((void *)locations);
			return (c_path);
		}
		else
			free(c_path);
		path_index++;
	}
	return (free_and_null_end((char **)locations, args));
}
