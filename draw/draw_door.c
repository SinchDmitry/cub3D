/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:02:59 by utygett           #+#    #+#             */
/*   Updated: 2022/03/23 14:22:17 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_ray_param(t_data_mlx *data)
{
	data->am_s->spr_img[0].x_ray = data->am_s->spr_img[0].x - data->map->play.x;
	data->am_s->spr_img[0].y_ray = data->am_s->spr_img[0].y - data->map->play.y;
	data->am_s->spr_img[1].x_ray = data->am_s->spr_img[1].x - data->map->play.x;
	data->am_s->spr_img[1].y_ray = data->am_s->spr_img[1].y - data->map->play.y;
	data->am_s->spr_img[2].x_ray = data->am_s->spr_img[2].x - data->map->play.x;
	data->am_s->spr_img[2].y_ray = data->am_s->spr_img[2].y - data->map->play.y;
	data->am_s->spr_img[3].x_ray = data->am_s->spr_img[3].x - data->map->play.x;
	data->am_s->spr_img[3].y_ray = data->am_s->spr_img[3].y - data->map->play.y;
	data->am_s->comp_img.x_ray = data->am_s->comp_img.x - data->map->play.x;
	data->am_s->comp_img.y_ray = data->am_s->comp_img.y - data->map->play.y;
	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
}

static void	calc_sprite_param(t_data_mlx *data, t_spr_tex *img, int num)
{
	img[num].t_x = data->am_s->inv * (data->map->play.dir_y * \
		img[num].x_ray - data->map->play.dir_x * img[num].y_ray);
	img[num].t_y = data->am_s->inv * (-data->map->cam.pl_y * \
		img[num].x_ray + data->map->cam.pl_x * img[num].y_ray);
	img[num].pos_spr_x = (int)((WIDTH / 2) * (1 + \
		img[num].t_x / img[num].t_y));
	img[num].h_spr = abs((int)(HEIGHT / img[num].t_y));
	img[num].dr_st_y = -(img[num].h_spr / 2) + HEIGHT / 2;
}

static void	calc_sprite_sector(t_data_mlx *data, t_spr_tex *img, int num)
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
}

void	draw_sprite(t_data_mlx *data, t_spr_tex *img, int n, int cost)
{
	int	i;
	int	j;
	int	f;

	init_ray_param(data);
	calc_sprite_param(data, img, n);
	calc_sprite_sector(data, img, n);
	i = img[n].dr_st_x - 1;
	f = 0;
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

void	check_door(t_data_mlx *data)
{
	static int	i_among[DOOR_NUM];
	int			door_n;

	door_n = 0;
	while (door_n < DOOR_NUM)
	{
		if (data->am_s->door_img[door_n].shot \
			&& !data->am_s->door_img[door_n].dead)
		{
			++i_among[door_n];
			if (i_among[door_n] == SPR_COSTUME - 1)
				data->am_s->door_img[door_n].dead = 1;
		}
		data->am_s->door_img[door_n].c_num = i_among[door_n];
		if (!data->am_s->door_img[door_n].dead)
			draw_sprite(data, data->am_s->door_img, door_n, \
				data->am_s->door_img[door_n].c_num);
		else
			draw_sprite(data, data->am_s->door_img, door_n, SPR_COSTUME - 1);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, door_n);
		door_n++;
	}
}
