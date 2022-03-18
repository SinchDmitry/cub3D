/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/18 22:00:05 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	calc_sprite_param(t_data_mlx *data, int num)
{
	data->am_s->spr_img[0].x_ray = data->am_s->spr_img[0].x - data->map->play.x;
	data->am_s->spr_img[0].y_ray = data->am_s->spr_img[0].y - data->map->play.y;
	data->am_s->spr_img[1].x_ray = data->am_s->spr_img[1].x - data->map->play.x;
	data->am_s->spr_img[1].y_ray = data->am_s->spr_img[1].y - data->map->play.y;
	data->am_s->spr_img[2].x_ray = data->am_s->spr_img[2].x - data->map->play.x;
	data->am_s->spr_img[2].y_ray = data->am_s->spr_img[2].y - data->map->play.y;
	data->am_s->spr_img[3].x_ray = data->am_s->spr_img[3].x - data->map->play.x;
	data->am_s->spr_img[3].y_ray = data->am_s->spr_img[3].y - data->map->play.y;
	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
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
}

static void	calc_sprite_sector(t_spr *am_s, int num)
{
	if (am_s->spr_img[num].dr_st_y < 0)
		am_s->spr_img[num].dr_st_y = 0;
	am_s->spr_img[num].dr_f_y = am_s->spr_img[num].h_spr / 2 + HEIGHT / 2;
	if (am_s->spr_img[num].dr_f_y > HEIGHT)
		am_s->spr_img[num].dr_f_y = HEIGHT - 1;
	am_s->spr_img[num].w_spr = abs((int)(HEIGHT / am_s->spr_img[num].t_y));
	am_s->spr_img[num].dr_st_x = -am_s->spr_img[num].w_spr / 2 + \
		am_s->spr_img[num].pos_spr_x;
	if (am_s->spr_img[num].dr_st_x < 0)
		am_s->spr_img[num].dr_st_x = 0;
	am_s->spr_img[num].dr_f_x = am_s->spr_img[num].w_spr / 2 + \
		am_s->spr_img[num].pos_spr_x;
	if (am_s->spr_img[num].dr_f_x >= WIDTH)
		am_s->spr_img[num].dr_f_x = WIDTH - 1;
}

void	draw_sprite(t_data_mlx *data, t_spr_tex *img, int n, int cost)
{
	int	i;
	int	j;

	calc_sprite_param(data, n);
	calc_sprite_sector(data->am_s, n);
	i = img[n].dr_st_x - 1;
	while (++i < img[n].dr_f_x)
	{
		img[n].tex_x = ((int)(256 * (i - (-img[n].w_spr / 2 + \
		img[n].pos_spr_x)) * img[n].costumes[cost].img_w / img[n].w_spr) / 256);
		if (img[n].t_y > 0 && i > 0 && i < WIDTH && \
			img[n].t_y < data->sector[i])
		{
			j = img[n].dr_st_y - 1;
			while (++j < img[n].dr_f_y)
			{
				img[n].d = j * 256 - HEIGHT * 128 + img[n].h_spr * 128;
				img[n].tex_y = (((img[n].d * img[n].costumes[cost].img_h) \
				/ img[n].h_spr) / 256);
				my_mlx_pixel_put(data, i, j + data->map->cam.vertilcal_pos, \
					my_mlx_get_pixel(data, img[n].tex_x, \
					img[n].tex_y, n + 10));
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
	while (spr_num < SPR_NUM)
	{
		if (data->am_s->spr_img[spr_num].shot \
			&& !data->am_s->spr_img[spr_num].dead)
		{
			++i_among;
			if (i_among == SPR_COSTUME - 1)
				data->am_s->spr_img[spr_num].dead = 1;
		}
		data->am_s->spr_img[spr_num].c_num = i_among;
		if (!data->am_s->spr_img[spr_num].dead)
			draw_sprite(data, data->am_s->spr_img, spr_num, data->am_s->spr_img[spr_num].c_num);
		else
			draw_sprite(data,  data->am_s->spr_img, spr_num, SPR_COSTUME - 1);
		spr_num++;
	}
	draw_aim(data);
	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
		attack_weapon(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
