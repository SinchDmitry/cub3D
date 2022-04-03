/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:38:39 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 13:21:51 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_res(t_data_mlx *data, t_spr_tex **img, char **r, int val)
{
	if (val == FLOOR || val == SKY)
		if ((!r[0] || !r[1] || !r[2]) || \
		(ft_atoi(r[0]) > 255 || ft_atoi(r[1]) > 255 || ft_atoi(r[2]) > 255))
			error_end(2);
	if (val == AMONG || val == COMP || val == DOOR)
		if ((!r[0] || !r[1]) || (ft_atoi(r[0]) > data->map->width || \
		ft_atoi(r[1]) > data->map->height))
			error_end(2);
	if (val == FLOOR)
	{
		data->map->floor_color = create_trgb(data->map->floor_color, \
			ft_atoi(r[0]), ft_atoi(r[1]), ft_atoi(r[2]));
		data->map->flags.floor = 1;
	}
	else if (val == SKY)
	{
		data->map->sky_color = create_trgb(data->map->sky_color, \
			ft_atoi(r[0]), ft_atoi(r[1]), ft_atoi(r[2]));
		data->map->flags.sky = 1;
	}
	else if (val == AMONG)
		add_back_or_new(img, AMONG_SIZE, ft_atoi(r[0]), ft_atoi(r[1]));
	else if (val == COMP || val == DOOR)
		add_back_or_new(img, FULL_SIZE, ft_atoi(r[0]), ft_atoi(r[1]));
}

static void	spr_rgb_parse(t_data_mlx *data, t_spr_tex **img, char *arg, int val)
{
	char	**res;
	char	*res_str;
	int		i;

	res_str = NULL;
	i = -1;
	while (arg[++i])
		if (!space(arg[i]))
			res_str = ft_chrjoin(res_str, arg[i]);
	save_point(res_str, P_FRONT);
	while (res_str[i + 1])
		if (res_str[i] == ',' && res_str[i + 1] == ',')
			error_end(1);
	i = -1;
	while (res_str[++i])
		if ((res_str[i] < 48 || res_str[i] > 57) && res_str[i] != ',')
			error_end(1);
	res = ft_split((const char *)arg, ',');
	if (!res)
		error_end(3);
	save_point(res, P_BACK);
	i = -1;
	while (res[++i])
		save_point(res[i], P_FRONT);
	parse_res(data, img, res, val);
}

void	objects_parse(t_data_mlx *data, char *arg, int val)
{
	while (*arg++ != 32)
		if (*arg == '\n' || !*arg)
			error_end(2);
	arg = ft_isspace_strtrim(arg);
	if (val == SKY)
	{
		if (data->map->flags.sky)
			error_end(1);
		spr_rgb_parse(data, NULL, arg, val);
	}
	else if (val == FLOOR)
	{
		if (data->map->flags.floor)
			error_end(1);
		spr_rgb_parse(data, NULL, arg, val);
	}
	else if (val == AMONG)
		spr_rgb_parse(data, &data->am_s->spr_img, arg, val);
	else if (val == COMP)
		spr_rgb_parse(data, &data->am_s->comp_img, arg, val);
	else if (val == DOOR)
		spr_rgb_parse(data, &data->am_s->door_img, arg, val);
	else
		error_end(2);
}

void	check_valid_file(char *str)
{
	int		id;
	int		read_byte;
	char	buf[2];

	id = open(str, O_RDONLY);
	if (id < 1)
		error_end(2);
	read_byte = read(id, buf, 1);
	if (read_byte < 0)
	{
		close(id);
		error_end(2);
	}
	close(id);
}
