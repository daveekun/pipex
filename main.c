/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:12:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/11/24 13:41:34 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	char *const params[] = {"ls", "-a", "/Users/dhorvath", NULL};
	char *const env[] = {NULL};

	execve("/bin/ls", params, env);
}
