/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/18 21:00:06 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	init_sprite(t_data_mlx *data)
{
	data->am_s->spr_img[0].x = 22.5;
	data->am_s->spr_img[0].y = 4.5;
	data->am_s->spr_img[0].x_ray = data->am_s->spr_img[0].x - data->map->play.x;
	data->am_s->spr_img[0].y_ray = data->am_s->spr_img[0].y - data->map->play.y;
	data->am_s->spr_img[1].x = 11.5;
	data->am_s->spr_img[1].y = 10.5;
	data->am_s->spr_img[1].x_ray = data->am_s->spr_img[1].x - data->map->play.x;
	data->am_s->spr_img[1].y_ray = data->am_s->spr_img[1].y - data->map->play.y;
	data->am_s->spr_img[2].x = 26.5;
	data->am_s->spr_img[2].y = 15.5;
	data->am_s->spr_img[2].x_ray = data->am_s->spr_img[2].x - data->map->play.x;
	data->am_s->spr_img[2].y_ray = data->am_s->spr_img[2].y - data->map->play.y;
	data->am_s->spr_img[3].x = 23.5;
	data->am_s->spr_img[3].y = 23.5;
	data->am_s->spr_img[3].x_ray = data->am_s->spr_img[3].x - data->map->play.x;
	data->am_s->spr_img[3].y_ray = data->am_s->spr_img[3].y - data->map->play.y;
	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
}

void	draw_sprite(t_data_mlx *data, int num, int cost)
{
	int	i;
	int	j;
	int	tex_x;
	int	tex_y;
	int	d;

	init_sprite(data);
	data->am_s->spr_img[num].t_x = data->am_s->inv * (data->map->play.dir_y * \
		data->am_s->spr_img[num].x_ray - data->map->play.dir_x * \
		data->am_s->spr_img[num].y_ray);
	data->am_s->spr_img[num].t_y = data->am_s->inv * (-data->map->cam.pl_y * \
		data->am_s->spr_img[num].x_ray + data->map->cam.pl_x * \
		data->am_s->spr_img[num].y_ray);
	data->am_s->spr_img[num].pos_spr_x = (int)((WIDTH / 2) * (1 + \
		data->am_s->spr_img[num].t_x / data->am_s->spr_img[num].t_y));
	data->am_s->spr_img[num].h_spr = \
		abs((int)(HEIGHT / data->am_s->spr_img[num].t_y));
	data->am_s->spr_img[num].dr_st_y = -(data->am_s->spr_img[num].h_spr / 2) \
		+ HEIGHT / 2;
	if (data->am_s->spr_img[num].dr_st_y < 0)
		data->am_s->spr_img[num].dr_st_y = 0;
	data->am_s->spr_img[num].dr_f_y = data->am_s->spr_img[num].h_spr / 2 + \
		HEIGHT / 2;
	if (data->am_s->spr_img[num].dr_f_y > HEIGHT)
		data->am_s->spr_img[num].dr_f_y = HEIGHT - 1;
	data->am_s->spr_img[num].w_spr = \
		abs((int)(HEIGHT / data->am_s->spr_img[num].t_y));
	data->am_s->spr_img[num].dr_st_x = -data->am_s->spr_img[num].w_spr / 2 + \
		data->am_s->spr_img[num].pos_spr_x;
	if (data->am_s->spr_img[num].dr_st_x < 0)
		data->am_s->spr_img[num].dr_st_x = 0;
	data->am_s->spr_img[num].dr_f_x = data->am_s->spr_img[num].w_spr / 2 + \
		data->am_s->spr_img[num].pos_spr_x;
	if (data->am_s->spr_img[num].dr_f_x >= WIDTH)
		data->am_s->spr_img[num].dr_f_x = WIDTH - 1;
	i = data->am_s->spr_img[num].dr_st_x - 1;
	while (++i < data->am_s->spr_img[num].dr_f_x)
	{
		tex_x = ((int)(256 * (i - (-data->am_s->spr_img[num].w_spr / 2 + \
			data->am_s->spr_img[num].pos_spr_x)) * \
			data->am_s->spr_img[num].costumes[cost].img_w / \
			data->am_s->spr_img[num].w_spr) / 256);
		if (data->am_s->spr_img[num].t_y > 0 && i > 0 && \
			i < WIDTH && data->am_s->spr_img[num].t_y < data->sector[i])
		{
			j = data->am_s->spr_img[num].dr_st_y - 1;
			while (++j < data->am_s->spr_img[num].dr_f_y)
			{
				d = j * 256 - HEIGHT * 128 + \
					data->am_s->spr_img[num].h_spr * 128;
				tex_y = (((d * data->am_s->spr_img[num].costumes[cost].img_h) / \
					data->am_s->spr_img[num].h_spr) / 256);
				my_mlx_pixel_put(data, i, j + data->map->cam.vertilcal_pos, \
					my_mlx_get_pixel(data, tex_x, tex_y, num + 10));
          		// if((color & 0x00FFFFFF) != 0) 
				// 	buffer[j][i] = color; // buffer ?
			}
		}
	}
}

void	draw_objects(t_data_mlx *data)
{
	static int	i_among;
	int			spr_num;

	spr_num = 0;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	draw_invis_background(data, WIDTH, HEIGHT);
	// while (spr_num < SPR_NUM)
	// {
		if (data->am_s->spr_img[spr_num].shot \
			&& !data->am_s->spr_img[spr_num].dead)
		// if (data->am_s->spr_img[spr_num][0].shot \
			&& !data->am_s->spr_img[spr_num][0].dead)
		{
			++i_among;
			if (i_among == SPR_COSTUME - 1)
				data->am_s->spr_img[spr_num].dead = 1;
				// data->am_s->spr_img[spr_num][0].dead = 1;
		}
		// if (!data->am_s->spr_img[spr_num][0].dead)
		data->am_s->spr_img[spr_num].c_num = i_among;
		if (!data->am_s->spr_img[spr_num].dead)
			// draw_sprite(data, spr_num, i_among);
			draw_sprite(data, 0, data->am_s->spr_img[spr_num].c_num);
		else
		{
			// draw_sprite(data, spr_num, SPR_COSTUME - 1);
			draw_sprite(data, 0, SPR_COSTUME - 1);
			// sleep(5);
		}
		// printf("%d\n", i_among);
		// spr_num++;
	// }
	draw_aim(data);
	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
		attack_weapon(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
