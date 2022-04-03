/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:31:29 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 13:47:54 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**get_line_file(int fd)
{
	char	ch;
	char	*res;
	char	**string;
	int		i;

	i = -1;
	res = NULL;
	string = NULL;
	if (fd >= 0)
	{
		while (read(fd, &ch, 1))
			res = ft_chrjoin(res, ch);
		res = ft_chrjoin(res, '\0');
		string = ft_split(res, '\n');
		if (!string)
			error_end(1);
		save_point(string, 2);
		save_point(res, 2);
		while (string[++i])
			save_point(string[i], 2);
		return (string);
	}
	error_end(1);
	return (NULL);
}
