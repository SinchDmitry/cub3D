/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:45:10 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 23:30:56 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	texture_parse_ew(t_data_mlx *data, char **arg, int val)
{
	if (val == WEST)
	{
		if (data->map->flags.west)
			error_end(1);
		data->map->texture->west = ft_strdup_error_end(arg[1]);
		check_valid_file(data->map->texture->west);
		data->map->flags.west = 1;
		return (1);
	}
	else if (val == EAST)
	{
		if (data->map->flags.east)
			error_end(1);
		data->map->texture->east = ft_strdup_error_end(arg[1]);
		check_valid_file(data->map->texture->east);
		data->map->flags.east = 1;
		return (1);
	}
	return (0);
}

static int	texture_parse_ns(t_data_mlx *data, char **arg, int val)
{
	if (val == NORTH)
	{
		if (data->map->flags.north)
			error_end(1);
		data->map->texture->north = ft_strdup_error_end(arg[1]);
		check_valid_file(data->map->texture->north);
		data->map->flags.north = 1;
		return (1);
	}
	else if (val == SOUTH)
	{
		if (data->map->flags.south)
			error_end(1);
		data->map->texture->south = ft_strdup_error_end(arg[1]);
		check_valid_file(data->map->texture->south);
		data->map->flags.south = 1;
		return (1);
	}
	return (0);
}

static void	param_parse(t_data_mlx *data, char **arg, int mode, int val)
{
	int	i;

	i = 0;
	if (mode == RGB || mode == SPRITE || mode == DOOR)
		objects_parse(data, *arg, val);
	else if (mode == TEXTURE)
	{
		while (arg[i])
			i++;
		if (i != 2)
			error_end(2);
		if (!texture_parse_ew(data, arg, val))
			texture_parse_ns(data, arg, val);
	}
}

static int	no_key(int flag, char **arg)
{
	int	i;

	i = -1;
	flag = -2;
	while (arg[0][++i])
	{
		if (arg[0][i] != '1')
			return (0);
	}
	return (flag);
}

int	key_compare(t_data_mlx *data, char **arg, char *map_str)
{
	int	flag;

	flag = -1;
	if (!ft_strcmp(arg[0], "C"))
		param_parse(data, &map_str, RGB, SKY);
	else if (!ft_strcmp(arg[0], "F"))
		param_parse(data, &map_str, RGB, FLOOR);
	else if (!ft_strcmp(arg[0], "NO"))
		param_parse(data, arg, TEXTURE, NORTH);
	else if (!ft_strcmp(arg[0], "SO"))
		param_parse(data, arg, TEXTURE, SOUTH);
	else if (!ft_strcmp(arg[0], "WE"))
		param_parse(data, arg, TEXTURE, WEST);
	else if (!ft_strcmp(arg[0], "EA"))
		param_parse(data, arg, TEXTURE, EAST);
	else if (!ft_strcmp(arg[0], "AM"))
		param_parse(data, &map_str, SPRITE, AMONG);
	else if (!ft_strcmp(arg[0], "CP"))
		param_parse(data, &map_str, SPRITE, COMP);
	else if (!ft_strcmp(arg[0], "D"))
		param_parse(data, &map_str, SPRITE, DOOR);
	else
		flag = no_key(flag, arg);
	return (flag);
}
