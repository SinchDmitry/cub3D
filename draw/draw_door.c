/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:30 by utygett           #+#    #+#             */
/*   Updated: 2022/03/24 10:48:55 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	calc_sprite_door_param(t_data_mlx *data, t_spr_tex *img, int num)
{
	img[num].t_x = data->am_s->inv * (data->map->play.dir_y * \
		img[num].x_ray - data->map->play.dir_x * img[num].y_ray);
	img[num].t_y = data->am_s->inv * (-data->map->cam.pl_y * \
		img[num].x_ray + data->map->cam.pl_x * img[num].y_ray);
	img[num].pos_spr_x = (int)((WIDTH / 2) * (1 + \
		img[num].t_x / img[num].t_y));
	// img[num].pos_spr_x = (int)((WIDTH / 2); 
	img[num].h_spr = abs((int)(HEIGHT / img[num].t_y));
	img[num].dr_st_y = -(img[num].h_spr / 2) + HEIGHT / 2;
}

static void	calc_sprite_door_sector(t_data_mlx *data, t_spr_tex *img, int num)
{
	if (img[num].dr_st_y + data->map->cam.vertilcal_pos < 0)
		img[num].dr_st_y = -data->map->cam.vertilcal_pos;
	img[num].dr_f_y = img[num].h_spr / 2 + HEIGHT / 2;
	if (img[num].dr_f_y > HEIGHT - data->map->cam.vertilcal_pos)
		img[num].dr_f_y = HEIGHT - data->map->cam.vertilcal_pos - 1;
	img[num].w_spr = abs((int)(HEIGHT / img[num].t_y));
	img[num].dr_st_x = -img[num].w_spr / 2 + \
		img[num].pos_spr_x;
	if (img[num].dr_st_x < 0)
		img[num].dr_st_x = 0;
	img[num].dr_f_x = img[num].w_spr / 2 + \
		img[num].pos_spr_x;
	if (img[num].dr_f_x >= WIDTH)
		img[num].dr_f_x = WIDTH - 1;

	if(num == 1)
	{
		printf("start : %d = img[num].w_spr(%d)/2+img[num].pos_spr_x(%d)\n", img[num].dr_st_x, -img[num].w_spr, img[num].pos_spr_x);
		printf("img[num].w_spr(%d) = 700 / img[num].t_y(%f)\n", img[num].w_spr, img[num].t_y);
		printf("img[num].pos_spr_x(%d = (int)((1000 / 2) * (1 +img[num].t_x(%f) / img[num].t_y(%f))\n", img[num].pos_spr_x, img[num].t_x, img[num].t_y);
	}
}


static void	init_ray_door_param(t_data_mlx *data)
{
	data->am_s->door_img[0].x_ray = data->am_s->door_img[0].x - data->map->play.x;
	data->am_s->door_img[0].y_ray = data->am_s->door_img[0].y - data->map->play.y;
	data->am_s->door_img[1].x_ray = data->am_s->door_img[1].x - data->map->play.x;
	data->am_s->door_img[1].y_ray = data->am_s->door_img[1].y - data->map->play.y;
	data->am_s->door_img[2].x_ray = data->am_s->door_img[2].x - data->map->play.x;
	data->am_s->door_img[2].y_ray = data->am_s->door_img[2].y - data->map->play.y;
	data->am_s->door_img[3].x_ray = data->am_s->door_img[3].x - data->map->play.x;
	data->am_s->door_img[3].y_ray = data->am_s->door_img[3].y - data->map->play.y;
	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
}

void	draw_door_sprite(t_data_mlx *data, t_spr_tex *img, int n, int cost)
{
	int	i;
	int	j;
	int	f;

	init_ray_door_param(data);
	calc_sprite_door_param(data, img, n);
	calc_sprite_door_sector(data, img, n);
	i = img[n].dr_st_x - 1;
	f = 0;
	// if(n == 1)
	// 	printf(" i : %d dr_f_x : %d num : %d\n", i, img[n].dr_f_x, n);
	img[n].fact_st_x = 0;
	img[n].fact_f_x = 0;
	while (++i < img[n].dr_f_x)
	{
		img[n].tex_x = ((int)(256 * (i - (-img[n].w_spr / 2 + \
		img[n].pos_spr_x)) * img[n].costumes[cost].img_w / img[n].w_spr) / 256);
		if (img[n].t_y > 0 && i > 0 && i < WIDTH && \
			img[n].t_y < data->sector[i])
		{
			if (!f)
			{
				img[n].fact_st_x = i;
				f = 1;
			}
			img[n].fact_f_x = i;
			j = img[n].dr_st_y - 1;
			while (++j < img[n].dr_f_y)
			{
				img[n].d = j * 256 - HEIGHT * 128 + img[n].h_spr * 128;
				img[n].tex_y = (((img[n].d * img[n].costumes[cost].img_h) \
				/ img[n].h_spr) / 256);
				my_mlx_pixel_put(data, i, j + data->map->cam.vertilcal_pos, \
					my_mlx_get_pixel(img[n].costumes[cost], img[n].tex_x, \
						img[n].tex_y));
			}
		}
	}
}