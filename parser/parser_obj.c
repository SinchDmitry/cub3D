/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:38:39 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/31 18:21:54 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parse_res(t_data_mlx *data, t_spr_tex *img, char **res, int val)
{
	if (val == FLOOR)
	{
		data->map->floor_color = create_trgb(data->map->floor_color, \
			ft_atoi(res[0]), ft_atoi(res[1]), ft_atoi(res[2]));
		data->map->flags.floor = 1;
	}
	else if (val == SKY)
	{
		data->map->sky_color = create_trgb(data->map->sky_color, \
			ft_atoi(res[0]), ft_atoi(res[1]), ft_atoi(res[2]));
		data->map->flags.sky = 1;
	}
	else if (val == SPRITE)
		add_back_or_new(&img, AMONG_SIZE, ft_atoi(res[0]), ft_atoi(res[1]));
	else if (val == COMP)
		add_back_or_new(&img, FULL_SIZE, ft_atoi(res[0]), ft_atoi(res[1]));
}

static void	spr_rgb_parse(t_data_mlx *data, t_spr_tex *img, char *arg, int val)
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
	i = -1;
	while (res_str[++i + 1])
		if (res_str[i] == ',' && res_str[i + 1] == ',')
			error_end(2);
	res = ft_split((const char *)arg, ',');
	if (!res)
		error_end(3);
	save_point(res, P_BACK);
	i = -1;
	while (res[++i])
		save_point(res[i], P_FRONT);
	parse_res(data, img, res, val);
}

void	objects_parse(t_data_mlx *data, char **arg, int val)
{
	if (val == SKY)
	{
		if (data->map->flags.sky)
			error_end(1);
		spr_rgb_parse(data, NULL, *arg + 1, val);
	}
	else if (val == FLOOR)
	{
		if (data->map->flags.floor)
			error_end(1);
		spr_rgb_parse(data, NULL, *arg + 1, val);
	}
	else if (val == AMONG)
		spr_rgb_parse(data, data->am_s->spr_img, *arg + 1, val);
	else if (val == COMP)
		spr_rgb_parse(data, data->am_s->comp_img, *arg + 1, val);
}
