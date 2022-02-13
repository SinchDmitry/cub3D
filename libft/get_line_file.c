/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:31:29 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/12 23:17:16 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../cub.h"

char	**get_line_file(int fd)
{
	long	byte;
	char	ch;
	char	*res;
	char	**string;

	res = NULL;
	string = NULL;
	if (fd >= 0)
	{
		while (read(fd, &ch, 1))
			res = ft_chrjoin(res, ch);
		res = ft_chrjoin(res, '\0');
		string = ft_split(res, '\n');
		if (!string)
			error_end(5);
		return (string);
	}
	error_end(5);
	return (NULL);
}

int	main(int argc, char **argv)
{
	char	**res;
	int		fd;
	int		i;

	res = NULL;
	i = -1;
	fd = open(argv[1], O_RDONLY);
	printf("%d\n", fd);
	res = get_line_file(fd);
	while (res[++i])
		printf("#%d : %s\n", i, res[i]);
	return (0);
}
