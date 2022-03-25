/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:45:10 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/25 21:55:22 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	rgb_parse(t_rgb *str, char *arg, int i)
{
	char	**rgb;
	char	*rgb_str;

	rgb_str = NULL;
	i = -1;
	while (arg[++i])
		if (!space(arg[i]))
			rgb_str = ft_chrjoin(rgb_str, arg[i]);
	save_point(rgb_str, P_FRONT);
	i = -1;
	while (rgb_str[++i + 1])
		if (rgb_str[i] == ',' && rgb_str[i + 1] == ',')
			error_end(2);
	rgb = ft_split((const char *)arg, ',');
	if (!rgb)
		error_end(3);
	save_point(rgb, P_BACK);
	i = -1;
	while (rgb[++i])
		save_point(rgb[i], P_FRONT);
	str->r = ft_atoi(rgb[0]);
	str->g = ft_atoi(rgb[1]);
	str->b = ft_atoi(rgb[2]);
}

static void	param_parse(t_info *map, char **arg, int mode, int val)
{
	int		i;

	i = 0;
	if (mode == RGB)
	{
		if (val == SKY)
			rgb_parse(map->sky, *arg + 1, i);
		else if (val == FLOOR)
			rgb_parse(map->floor, *arg + 1, i);
	}
	else if (mode == TEXTURE)
	{
		while (arg[i])
			i++;
		if (i != 2)
			error_end(2);
		if (val == NORTH)
			map->texture->north = ft_strdup_error_end(arg[1]);
		else if (val == SOUTH)
			map->texture->south = ft_strdup_error_end(arg[1]);
		else if (val == WEST)
			map->texture->west = ft_strdup_error_end(arg[1]);
		else if (val == EAST)
			map->texture->east = ft_strdup_error_end(arg[1]);
	}
}

static int	key_compare(t_info *map, char **arg, char *map_str)
{
	int	flag;
	int	i;

	flag = -1;
	i = -1;
	if (!ft_strcmp(arg[0], "C"))
		param_parse(map, &map_str, RGB, SKY);
	else if (!ft_strcmp(arg[0], "F"))
		param_parse(map, &map_str, RGB, FLOOR);
	else if (!ft_strcmp(arg[0], "NO"))
		param_parse(map, arg, TEXTURE, NORTH);
	else if (!ft_strcmp(arg[0], "SO"))
		param_parse(map, arg, TEXTURE, SOUTH);
	else if (!ft_strcmp(arg[0], "WE"))
		param_parse(map, arg, TEXTURE, WEST);
	else if (!ft_strcmp(arg[0], "EA"))
		param_parse(map, arg, TEXTURE, EAST);
	else if (!ft_strcmp(arg[0], "AM"))
		param_parse(map, arg, SPRITE, EAST);
	else if (!ft_strcmp(arg[0], "CP"))
		param_parse(map, arg, SPRITE, EAST);
	else if (!ft_strcmp(arg[0], "D"))
		param_parse(map, arg, SPRITE, EAST);
	else
	{
		flag = -2;
		while (arg[0][++i])
			if (arg[0][i] != '1')
				return (0);
	}
	return (flag);
}

int	param_map(t_info *map, char **map_str)
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
		prm = key_compare(map, tmp, map_str[i]);
		if (prm == -1)
			map->height--;
		else if (!prm)
			error_end(2);
		else if (prm == -2)
			break ;
	}
	return (i);
}

/*

data->am_s->door_img[0].x = 8;
data->am_s->door_img[0].y = 12.5;
data->am_s->door_img[1].x = 6;
data->am_s->door_img[1].y = 12.5;
data->am_s->door_img[2].x = 14.5;
data->am_s->door_img[2].y = 22;
data->am_s->door_img[3].x = 24;
data->am_s->door_img[3].y = 14.5;

data->am_s->spr_img[0].x = 22.5;
data->am_s->spr_img[0].y = 4.5;
data->am_s->spr_img[1].x = 38.5;
data->am_s->spr_img[1].y = 10.5;
data->am_s->spr_img[2].x = 26.5;
data->am_s->spr_img[2].y = 15.5;
data->am_s->spr_img[3].y = 23.5;
data->am_s->spr_img[3].x = 23.5;

data->am_s->comp_img.x = 11;
data->am_s->comp_img.y = 11;
*/