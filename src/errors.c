/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:21:17 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/17 13:53:53 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf.h"

int	print_usage(void)
{
	ft_printf("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	return (1);
}

int	print_error(char **params)
{
	free_args(params);
	perror("pipex");
	return (1);
}
