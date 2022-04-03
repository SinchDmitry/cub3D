/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:02 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 15:12:18 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	to_malloc_big(char const *s)
{
	size_t	i;
	size_t	f;

	i = 0;
	f = 0;
	if (s[0] && !space(s[0]))
	{
		f++;
		i++;
	}
	while (s[i + 1])
	{
		if (space(s[i]) && !space(s[i + 1]))
			f++;
		i++;
	}
	return (f + 1);
}

static void	delall(char	**res, size_t a)
{
	while (a)
	{
		a--;
		free(res[a]);
	}
	free (res);
}

static char	**to_malloc_str(char **res, char const *s, long i, size_t size)
{
	size_t	a;
	long	j;
	size_t	f;

	i = -1;
	a = 0;
	while (s[++i] && a != size)
	{	
		if ((space(s[i]) && !space(s[i + 1])) || (s[i] && !space(s[i]) && !i))
		{
			j = i++;
			if (s[i - 1] && !space(s[i - 1]) && i == 1)
				j--;
			f = 0;
			while (s[i] && !space(s[i]))
				i++;
			res[a] = malloc (sizeof(char) * ((i--) - j));
			if (!res[a])
				delall(res, a);
			while (++j <= i)
				res[a][f++] = s[j];
			res[a++][f] = '\0';
		}	
	}
	return (res);
}

char	**ft_space_split(char const *s)
{
	size_t	i;
	size_t	f;
	char	**res;

	i = 0;
	if (s && *s)
	{
		f = to_malloc_big(s);
		res = malloc(sizeof(char *) * f);
		if (!res)
			return (NULL);
		res[f - 1] = NULL;
		return (to_malloc_str(res, s, i, f - 1));
	}
	res = malloc(sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	return (res);
}
