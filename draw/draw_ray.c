/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/08 19:37:44 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	init_camera(t_data_mlx *data, int x)
{
	data->map->camera.cam = 2 * x / (float)WIDTH - 1;
	data->map->camera.cam_dir_x = data->map->player.dir_x + \
		data->map->camera.pl_x * data->map->camera.cam;
	data->map->camera.cam_dir_y = data->map->player.dir_y + \
		data->map->camera.pl_y * data->map->camera.cam;
	data->map->camera.delta_dir_x = fabsf(1 / data->map->camera.cam_dir_x);
	data->map->camera.delta_dir_y = fabsf(1 / data->map->camera.cam_dir_y);
	data->map->camera.ray_pos_x = (int)data->map->player.x;
	data->map->camera.ray_pos_y = (int)data->map->player.y;
}

static void	init_camera_move(t_data_mlx *data)
{
	if (data->map->camera.cam_dir_x < 0)
	{
		data->map->camera.step_x = -1;
		data->map->camera.side_dist_x = (data->map->player.x - \
			data->map->camera.ray_pos_x) * data->map->camera.delta_dir_x;
	}
	else
	{
		data->map->camera.step_x = 1;
		data->map->camera.side_dist_x = (data->map->camera.ray_pos_x + 1.0 - \
			data->map->player.x) * data->map->camera.delta_dir_x;
	}
	if (data->map->camera.cam_dir_y < 0)
	{
		data->map->camera.step_y = -1;
		data->map->camera.side_dist_y = (data->map->player.y - \
			data->map->camera.ray_pos_y) * data->map->camera.delta_dir_y;
	}
	else
	{
		data->map->camera.step_y = 1;
		data->map->camera.side_dist_y = (data->map->camera.ray_pos_y + 1.0 - \
			data->map->player.y) * data->map->camera.delta_dir_y;
	}
}

static void	ray_calc(t_data_mlx *data)
{
	if (data->map->camera.side_dist_x < data->map->camera.side_dist_y)
	{
		data->map->camera.side_dist_x += data->map->camera.delta_dir_x;
		data->map->camera.ray_pos_x += data->map->camera.step_x;
		data->map->camera.wall_dir = 0;
	}
	else
	{
		data->map->camera.side_dist_y += data->map->camera.delta_dir_y;
		data->map->camera.ray_pos_y += data->map->camera.step_y;
		data->map->camera.wall_dir = 1;
	}
}

void	ray_player(t_data_mlx *data, int flag)
{
	int		x;
	int		i;

	x = -1;
	while (++x < WIDTH)
	{
		init_camera(data, x);
		init_camera_move(data);
		i = -1;
		while (++i < VIEW_RANGE)
		{
			ray_calc(data);
			if (data->map->mapa[data->map->camera.ray_pos_y] \
				[data->map->camera.ray_pos_x].sym != '0')
				break ;
		}
		if (!flag)
			my_mlx_pixel_put(data, data->map->camera.ray_pos_x * TEXSIZE, \
				data->map->camera.ray_pos_y * TEXSIZE, GREEN_COL);
		if (data->map->camera.wall_dir)
			data->sector = (data->map->camera.side_dist_y - \
				data->map->camera.delta_dir_y);
		else
			data->sector = (data->map->camera.side_dist_x - \
				data->map->camera.delta_dir_x);
		if (flag)
			draw_ray_cast(data, x, HEIGHT / (data->sector), \
				step_counter_texture(0.00390625f, 0));
	}
}
