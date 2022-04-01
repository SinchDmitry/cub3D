/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:30 by utygett           #+#    #+#             */
/*   Updated: 2022/04/01 20:55:11 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	check_player_in_door(t_data_mlx *data, int i, int j)
{
	if(i == (int)data->map->play.y && j == (int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i + 1 == (int)data->map->play.y && j == (int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i + -1 == (int)data->map->play.y && j == (int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i == (int)data->map->play.y && j + 1 == (int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i == (int)data->map->play.y && j - 1 == (int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (data->map->mapa[i][j].door == -2)
		data->map->mapa[i][j].door = 2;
}

void	check_door_state(t_data_mlx *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (data->map->mapa[i][j].door_state > 0 && data->map->mapa[i][j].door_state < 10 && data->map->mapa[i][j].door == 1)
				++data->map->mapa[i][j].door_state;
			if(data->map->mapa[i][j].door_state > 0 && data->map->mapa[i][j].door_state <= 10 && data->map->mapa[i][j].door == 2)
				--data->map->mapa[i][j].door_state;
			if (data->map->mapa[i][j].door_state >= 10)
			{
				if (data->map->mapa[i][j].door > 0)
					data->map->mapa[i][j].door = -1;
				check_player_in_door(data, i, j);
			}
			if (data->map->mapa[i][j].door_state == 0 && data->map->mapa[i][j].door == 2)
				data->map->mapa[i][j].door = 1;
		}
	}
}

void	check_door(t_data_mlx *data)
{
	if(data->map->mapa[(int)data->map->play.y + 1][(int)data->map->play.x].door == 1 && data->keycode[E_KEY] && data->map->mapa[(int)data->map->play.y + 1][(int)data->map->play.x].door_state == 0)
		data->map->mapa[(int)data->map->play.y + 1][(int)data->map->play.x].door_state = 1;
	else if(data->map->mapa[(int)data->map->play.y - 1][(int)data->map->play.x].door == 1 && data->keycode[E_KEY] && data->map->mapa[(int)data->map->play.y - 1][(int)data->map->play.x].door_state == 0)
		data->map->mapa[(int)data->map->play.y - 1][(int)data->map->play.x].door_state = 1; 
	else if(data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + 1].door == 1 && data->keycode[E_KEY] && data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + 1].door_state == 0)
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + 1].door_state = 1;
	else if(data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - 1].door == 1 && data->keycode[E_KEY] && data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - 1].door_state == 0)
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - 1].door_state = 1;
	draw_door(data);
}

void	draw_door(t_data_mlx *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		if(data->door_struct[x].use)
		{
			while (++data->door_struct[x].start < data->door_struct[x].end)
			{
				data->door_struct[x].text_y = (int)data->door_struct[x].tex_pos & \
					(data->am_s->door_textures[0].img_h - 1);
				data->door_struct[x].tex_pos += data->door_struct[x].step;
				my_mlx_pixel_put(data, x, data->door_struct[x].start, my_mlx_get_pixel(data->am_s->door_textures[data->door_struct[x].door_state], \
					data->door_struct[x].text_x, data->door_struct[x].text_y));
			}
		}
		data->door_struct[x].use = 0;
	}
}

static void	ray_door_side(t_data_mlx *data, t_wall_tex *img, int x)
{
	if (x == WIDTH / 2)
		data->map->play.side_for_move = img->sym;
	img->tex_x = (int)(img->wall_x * (double)data->am_s->door_textures[img->sym].img_w);
	img->tex_x = data->am_s->door_textures[img->sym].img_w - img->tex_x - 1;
	img->step = 1.0 * data->am_s->door_textures[img->sym].img_w / img->line_height;
	img->tex_pos = (img->draw_start - data->map->cam.vertilcal_pos - \
		HEIGHT / 2 + img->line_height / 2) * img->step;
}

static void ray_door_draw_lines(t_data_mlx *data, int x)
{
	int	i;

	data->door_struct[x].use = 2;
	i = data->wall_img->draw_start - 1;
	while (++i < data->wall_img->draw_end)
	{
		data->wall_img->tex_y = (int)data->wall_img->tex_pos & \
			(data->am_s->door_textures[data->wall_img->sym].img_h - 1);
		data->wall_img->tex_pos += data->wall_img->step;
		data->wall_img->col = \
			my_mlx_get_pixel(data->am_s->door_textures[0], \
			data->wall_img->tex_x, data->wall_img->tex_y);
		my_mlx_pixel_put(data, x, i, data->wall_img->col);
	}
}

void	init_door_pixels(t_data_mlx *data, int x, int door_state)
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
	if (data->door_struct[x].use == 1)
		ray_door_draw_lines(data, x);
	else if (data->door_struct[x].use == 0)
	{
		data->door_struct[x].start = data->wall_img->draw_start - 1;
		data->door_struct[x].use = 1;
		data->door_struct[x].end = data->wall_img->draw_end;
		data->door_struct[x].text_x = data->wall_img->tex_x;
		data->door_struct[x].text_y = (int)data->wall_img->tex_pos & \
			(data->am_s->door_textures[data->wall_img->sym].img_h - 1);
		data->door_struct[x].step = data->wall_img->step;
		data->door_struct[x].tex_pos = data->wall_img->tex_pos;
		data->door_struct[x].door_state = door_state;
	}
}