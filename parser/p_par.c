/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_par.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:45:10 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/14 22:40:14 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	rgb_parse(t_rgb *str, char *arg)
{
	int		i;
	char	**rgb;
	char	*rgb_str;

	i = -1;
	while (arg[++i])
		if (!space(arg[i]))
			rgb_str = ft_chrjoin(rgb_str, arg[i]);
	i = -1;
	while (rgb_str[++i + 1])
		if (rgb_str[i] == ',' && rgb_str[i + 1] == ',')
			error_end(2);
	rgb = ft_split((const char *)arg, ',');
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		error_end(2);
	str->r = ft_atoi(rgb[0]);
	str->g = ft_atoi(rgb[1]);
	str->b = ft_atoi(rgb[2]);
}

static void	param_parse(t_info *map, char **arg, int mode, int val)
{
	int	i;

	i = 0;
	if (mode == RGB)
	{
		if (val == SKY)
			rgb_parse(map->sky, *arg + 1);
		else if (val == FLOOR)
			rgb_parse(map->floor, *arg + 1);
	}
	else if (mode == TEXTURE)
	{
		while (arg[i])
			i++;
		if (i != 2)
			error_end(2);
		if (val == NORTH)
			map->texture->north = ft_strdup(arg[1]);
		else if (val == SOUTH)
			map->texture->south = ft_strdup(arg[1]);
		else if (val == WEST)
			map->texture->west = ft_strdup(arg[1]);
		else if (val == EAST)
			map->texture->east = ft_strdup(arg[1]);
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
	else
	{
		flag = -2;
		while (arg[0][++i])
			if (arg[0][i] != '1')
				return (0);
	}
	return (flag);
}

char	**param_map(t_info *map, char **map_str)
{
	char	**tmp;
	int		prm;
	int		i;

	i = -1;
	prm = 0;
	while (map_str[++i])
	{
		tmp = ft_space_split(map_str[i]);
		// pointer
		prm = key_compare(map, tmp, map_str[i]);
		if (prm == -1)
			map->height--;
		else if (!prm)
			error_end(1);
		else if (prm == -2)
			break ;
	}
	return (map_str + i);
}
