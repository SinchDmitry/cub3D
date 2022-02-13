/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/12 19:53:32 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	param_info()
{
	
}

t_data	parser(int argc, char **argv)
{
	t_info	*map;
	char	*string;

	*map = (t_info){};
	map->fd = open(argv[1], O_RDONLY);
	if (argc != 2 || ft_strcmp_rev(argv[1], ".cub") || map->fd < 2)
		error_end(1);
	while (1)
	{
		
			
	}
}
