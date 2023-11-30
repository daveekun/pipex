/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:29:24 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/30 20:36:17 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include "libft/includes/ft_printf.h"
# include "libft/includes/libft.h"
# include <fcntl.h>

typedef struct s_command
{
	char		**params;
	char *const	env[1];
}	t_command;

char	*find_command(char **args);
int		error_return(int ret);
int		output_function(int pipefd[2], char *outfile, int pid, t_command cmd);
int		input_function(int pipefd[2], char *infile, int pid, t_command cmd);

#endif