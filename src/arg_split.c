/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvath <dhorvath@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:43:48 by dhorvath          #+#    #+#             */
/*   Updated: 2023/12/16 16:54:35 by dhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	skip_til(char c, char *s)
{
	int	i;

	i = 1;
	while (s[i - 1] && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	count_args(char *s, char c)
{
	int	i;
	int	old_i;	
	int	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		old_i = i;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				i += skip_til(s[i], &s[i]);
			i++;
		}
		if (i != old_i)
			words++;
	}
	return (words);
}

char	**arg_split(char *s, char c)
{
	int		c_words;
	int		i;
	int		old_i;
	char	**res;

	i = 0;
	c_words = 0;
	res = ft_calloc(count_args(s, c) + 1, sizeof(char *));
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		old_i = i;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '\"')
				i += skip_til(s[i], &s[i]);
			i++;
		}
		if (i != old_i)
			res[c_words++] = ft_substr(s, old_i, i - old_i);
		if (!res[c_words - 1])
			free_args(res);
	}
	return (res);
}
