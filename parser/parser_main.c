/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 17:49:45 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	param_map(t_data_mlx *data, char **map_str)
{
	char	**tmp;
	int		prm;
	int		i;
	int		j;

	i = -1;
	prm = 0;
	while (map_str[++i])
	{
		j = -1;
		tmp = ft_space_split(map_str[i]);
		if (!tmp)
			error_end(3);
		save_point(tmp, P_BACK);
		while (tmp[++j])
			save_point(tmp[j], P_FRONT);
		prm = key_compare(data, tmp, map_str[i]);
		if (prm == -1)
			data->map->height--;
		else if (!prm)
			error_end(2);
		else if (prm == -2)
			break ;
	}
	return (i);
}

static void	map_struct(t_data_mlx *data, char **map_str)
{
	int	i;

	i = -1;
	if (data->map->height > HEIGHT || data->map->width > WIDTH)
		error_end(1);
	if (data->map->flags.east + data->map->flags.west + data->map->flags.north \
		+ data->map->flags.south + data->map->flags.floor + \
		data->map->flags.sky != 6)
		error_end(1);
	data->map->mapa = ft_calloc_error_end(sizeof(t_par_slot *), \
		data->map->height + 1, P_FRONT);
	while (++i < data->map->height)
		data->map->mapa[i] = ft_calloc_error_end(sizeof(t_par_slot), \
			(data->map->width), P_FRONT);
	map_create(data, map_str);
}

void	map_info(t_data_mlx *data, char **map_str)
{
	int	j;

	while (map_str[data->map->height])
	{
		j = 0;
		while (map_str[data->map->height][j])
			j++;
		if (j > data->map->width)
			data->map->width = j;
		data->map->height++;
	}
	map_struct(data, map_str + param_map(data, map_str));
}

void	parser(t_data_mlx *data, int argc, char **argv, int fd)
{
	char		**map_str;

	if (argc != 2 || ft_strcmp_rev(argv[1], ".cub") || fd < 2)
		error_end(1);
	data->am_s = ft_calloc_error_end(sizeof(t_data_tex), 1, P_FRONT);
	data->map = ft_calloc_error_end(sizeof(t_map_info), 1, P_BACK);
	data->map->texture = ft_calloc_error_end(sizeof(t_par_tex), 1, P_FRONT);
	data->map->fd = fd;
	data->map->flags = (t_par_f){};
	map_str = get_line_file(data->map->fd);
	map_info(data, map_str);
}
