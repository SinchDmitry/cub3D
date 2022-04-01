/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:23:06 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/01 22:22:17 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_cam(t_data_mlx *data, int x)
{
	data->map->cam.cam = 2 * x / (float)WIDTH - 1;
	data->map->cam.cam_dir_x = data->map->play.dir_x + \
		data->map->cam.pl_x * data->map->cam.cam;
	data->map->cam.cam_dir_y = data->map->play.dir_y + \
		data->map->cam.pl_y * data->map->cam.cam;
	data->map->cam.delta_dir_x = fabsf(1 / data->map->cam.cam_dir_x);
	data->map->cam.delta_dir_y = fabsf(1 / data->map->cam.cam_dir_y);
	data->map->cam.ray_pos_x = data->map->play.x;
	data->map->cam.ray_pos_y = data->map->play.y;
}

static void	init_cam_move(t_data_mlx *data)
{
	if (data->map->cam.cam_dir_x < 0)
	{
		data->map->cam.step_x = -1;
		data->map->cam.side_dist_x = (data->map->play.x - \
			data->map->cam.ray_pos_x) * data->map->cam.delta_dir_x;
	}
	else
	{
		data->map->cam.step_x = 1;
		data->map->cam.side_dist_x = (data->map->cam.ray_pos_x + 1.0 - \
			data->map->play.x) * data->map->cam.delta_dir_x;
	}
	if (data->map->cam.cam_dir_y < 0)
	{
		data->map->cam.step_y = -1;
		data->map->cam.side_dist_y = (data->map->play.y - \
			data->map->cam.ray_pos_y) * data->map->cam.delta_dir_y;
	}
	else
	{
		data->map->cam.step_y = 1;
		data->map->cam.side_dist_y = (data->map->cam.ray_pos_y + 1.0 - \
			data->map->play.y) * data->map->cam.delta_dir_y;
	}
}

void	ray_init(t_data_mlx *data, int x)
{
	init_cam(data, x);
	init_cam_move(data);
}

/* draw vertical line */
void	ray_draw_lines(t_data_mlx *data, int x)
{
	int	i;

	i = data->wall_img->draw_start - 1;
	while (++i < data->wall_img->draw_end)
	{
		data->wall_img->tex_y = (int)data->wall_img->tex_pos & \
			(data->am_s->wall_tex[(int)data->wall_img->sym].img_h - 1);
		data->wall_img->tex_pos += data->wall_img->step;
		data->wall_img->col = \
			my_mlx_get_pixel(data->am_s->wall_tex[(int)data->wall_img->sym], \
			data->wall_img->tex_x, data->wall_img->tex_y);
		my_mlx_pixel_put(data, x, i, data->wall_img->col);
	}
}
