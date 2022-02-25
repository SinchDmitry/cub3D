/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/02/25 22:30:13 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"


void	camera_line(t_data_mlx *data)
{
	if (data->map->player.dir == 'S')
	{
		data->map->player.dir_x = 0;
		data->map->player.dir_y = tan(1.571f / 2);
	}
	else if (data->map->player.dir == 'N')
	{
		data->map->player.dir_x = 0;
		data->map->player.dir_y = tan(-1.571f / 2);
	}
	else if (data->map->player.dir == 'W')
	{
		data->map->player.dir_x = tan(-1.571f / 2);
		data->map->player.dir_y = 0;
	}
	else if (data->map->player.dir == 'E')
	{
		data->map->player.dir_x = tan(1.571f / 2);
		data->map->player.dir_y = 0;
	}
	data->map->camera.pl_x = 0;
	data->map->camera.pl_y = tan(FOV / 2);
}

void	init_camera(t_data_mlx *data, int x)
{
	data->map->camera.cam = 2 * x / (float)WIDTH - 1;
	data->map->player.dir_x = data->map->player.dir_x + \
		data->map->camera.pl_x * data->map->camera.cam;
	data->map->player.dir_y = data->map->player.dir_y + \
		data->map->camera.pl_y * data->map->camera.cam;
	data->map->camera.delta_dir_x = fabsf(1 / data->map->player.dir_x);
	data->map->camera.delta_dir_y = fabsf(1 / data->map->player.dir_y);
	data->map->camera.ray_pos_x = (int)data->map->player.x;
	data->map->camera.ray_pos_y = (int)data->map->player.y;
}

void	init_camera_move(t_data_mlx *data)
{
	if (data->map->player.dir_x < 0)
	{
		data->map->camera.step_x = -1;
		data->map->camera.side_dist_x = (data->map->camera.ray_pos_x - \
			data->map->player.x) * data->map->camera.delta_dir_x;
	}
	else
	{
		data->map->camera.step_x = 1;
		data->map->camera.side_dist_x = (data->map->camera.ray_pos_x + (1.0 - \
			data->map->player.x)) * data->map->camera.delta_dir_x;
	}
	if (data->map->player.dir_y < 0)
	{
		data->map->camera.step_y = -1;
		data->map->camera.side_dist_y = (data->map->camera.ray_pos_y - \
			data->map->player.y) * data->map->camera.delta_dir_y;
	}
	else
	{
		data->map->camera.step_y = 1;
		data->map->camera.side_dist_x = (data->map->camera.ray_pos_y + (1.0 - \
			data->map->player.x)) * data->map->camera.delta_dir_y;
	}
}

void	ray_calc(t_data_mlx *data)
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

void	ray_player(t_data_mlx *data)
{
	// float	old_time;
	// float	time;
	int		x;
	int		i;

	x = -1;
	camera_line(data);
	while (++x < WIDTH)
	{
		init_camera(data, x);
		init_camera_move(data);
		i = -1;
		while (++i < VIEW_RANGE)
		{
			ray_calc(data);
			if (data->map->mapa[data->map->camera.ray_pos_x] \
					[data->map->camera.ray_pos_y].sym != '0')
				break ;
		}
		if (data->map->camera.wall_dir)
			data->sector[x] = (data->map->camera.side_dist_y - \
				data->map->camera.delta_dir_y);
		else
			data->sector[x] = (data->map->camera.side_dist_x - \
				data->map->camera.delta_dir_x);
	}
}
