/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:54:24 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 16:54:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ray_door_side(t_data_mlx *data, t_wall_tex *img, int x)
{
	if (x == WIDTH / 2)
		data->map->play.side_for_move = img->sym;
	img->tex_x = (int)(img->wall_x * \
		(double)data->am_s->door_tex[img->sym].img_w);
	img->tex_x = data->am_s->door_tex[img->sym].img_w - img->tex_x - 1;
	img->step = 1.0 * data->am_s->door_tex[img->sym].img_w / img->line_height;
	img->tex_pos = (img->draw_start - data->map->cam.vertilcal_pos - \
		HEIGHT / 2 + img->line_height / 2) * img->step;
}

static void	ray_door_draw_lines(t_data_mlx *data, int x)
{
	int	i;

	data->door_str[x].use = 2;
	i = data->wall_img->draw_start - 1;
	while (++i < data->wall_img->draw_end)
	{
		data->wall_img->tex_y = (int)data->wall_img->tex_pos & \
			(data->am_s->door_tex[data->wall_img->sym].img_h - 1);
		data->wall_img->tex_pos += data->wall_img->step;
		data->wall_img->col = \
			my_mlx_get_pixel(data->am_s->door_tex[0], \
			data->wall_img->tex_x, data->wall_img->tex_y);
		my_mlx_pixel_put(data, x, i, data->wall_img->col);
	}
}

void	init_door_pix(t_data_mlx *data, int x, int door_state)
{
	if (data->map->cam.wall_dir)
		data->sector[x] = (data->map->cam.side_dist_y - \
			data->map->cam.delta_dir_y);
	else
		data->sector[x] = (data->map->cam.side_dist_x - \
			data->map->cam.delta_dir_x);
	data->wall_img->line_height = (int)(HEIGHT / data->sector[x]);
	ray_wall_data(data, x);
	ray_door_side(data, data->wall_img, x);
	if (data->door_str[x].use == 1)
		ray_door_draw_lines(data, x);
	else if (data->door_str[x].use == 0)
	{
		data->door_str[x].start = data->wall_img->draw_start - 1;
		data->door_str[x].use = 1;
		data->door_str[x].end = data->wall_img->draw_end;
		data->door_str[x].text_x = data->wall_img->tex_x;
		data->door_str[x].text_y = (int)data->wall_img->tex_pos & \
			(data->am_s->door_tex[data->wall_img->sym].img_h - 1);
		data->door_str[x].step = data->wall_img->step;
		data->door_str[x].tex_pos = data->wall_img->tex_pos;
		data->door_str[x].door_state = door_state;
	}
}
