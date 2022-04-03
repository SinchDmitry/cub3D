/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/04/03 17:39:59 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ray_calc(t_data_mlx *data)
{
	if (data->map->cam.side_dist_x < data->map->cam.side_dist_y)
	{
		data->map->cam.side_dist_x += data->map->cam.delta_dir_x;
		data->map->cam.ray_pos_x += data->map->cam.step_x;
		data->map->cam.wall_dir = 0;
	}
	else
	{
		data->map->cam.side_dist_y += data->map->cam.delta_dir_y;
		data->map->cam.ray_pos_y += data->map->cam.step_y;
		data->map->cam.wall_dir = 1;
	}
}

static void	ray_length(t_data_mlx *data, int x)
{
	int	i;

	i = -1;
	while (++i < VIEW_RANGE)
	{
		ray_calc(data);
		if (data->map->mapa[data->map->cam.ray_pos_y] \
			[data->map->cam.ray_pos_x].door > 0)
			init_door_pix(data, x, data->map->mapa[data->map->cam.ray_pos_y] \
				[data->map->cam.ray_pos_x].door_state);
		if (data->map->mapa[data->map->cam.ray_pos_y] \
			[data->map->cam.ray_pos_x].sym != '0')
			break ;
	}
	if (data->map->cam.wall_dir)
		data->sector[x] = (data->map->cam.side_dist_y - \
			data->map->cam.delta_dir_y);
	else
		data->sector[x] = (data->map->cam.side_dist_x - \
			data->map->cam.delta_dir_x);
	data->wall_img->line_height = (int)(HEIGHT / data->sector[x]);
}

void	ray_wall_data(t_data_mlx *data, int x)
{
	data->wall_img->draw_start = -data->wall_img->line_height / 2 + \
		HEIGHT / 2 + data->map->cam.vertilcal_pos;
	if (data->wall_img->draw_start < 0)
		data->wall_img->draw_start = 0;
	data->wall_img->draw_end = data->wall_img->line_height / 2 + \
		HEIGHT / 2 + data->map->cam.vertilcal_pos;
	if (data->wall_img->draw_end >= HEIGHT)
		data->wall_img->draw_end = HEIGHT - 1;
	if (!data->map->cam.wall_dir)
		data->wall_img->wall_x = data->map->play.y + data->sector[x] * \
			data->map->cam.cam_dir_y;
	else
		data->wall_img->wall_x = data->map->play.x + data->sector[x] * \
			data->map->cam.cam_dir_x;
	data->wall_img->wall_x = data->wall_img->wall_x - \
		floor(data->wall_img->wall_x);
}

static void	ray_texture_side(t_data_mlx *data, t_wall_tex *img, int x)
{
	img->sym = 0;
	if (!data->map->cam.wall_dir)
	{
		if (data->map->cam.step_x == -1)
			img->sym = 0;
		else
			img->sym = 1;
	}
	else
	{
		if (data->map->cam.step_y == -1)
			img->sym = 2;
		else
			img->sym = 3;
	}
	if (x == WIDTH / 2)
		data->map->play.side_for_move = img->sym;
	img->tex_x = (int)(img->wall_x * \
		(double)data->am_s->wall_tex[img->sym].img_w);
	img->tex_x = data->am_s->wall_tex[img->sym].img_w - img->tex_x - 1;
	img->step = 1.0 * data->am_s->wall_tex[img->sym].img_w / img->line_height;
	img->tex_pos = (img->draw_start - data->map->cam.vertilcal_pos - \
		HEIGHT / 2 + img->line_height / 2) * img->step;
}

void	ray_play(t_data_mlx *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		ray_init(data, x);
		ray_length(data, x);
		if (data->door_str[x].use == 2)
			continue ;
		ray_wall_data(data, x);
		ray_texture_side(data, data->wall_img, x);
		ray_draw_lines(data, x);
	}
}
