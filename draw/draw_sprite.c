/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 17:33:23 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	check_obj_in_map(t_data_mlx *data, t_spr_tex *tmp_img)
{
	while (tmp_img)
	{
		if (data->map->mapa[(int)tmp_img->y][(int)tmp_img->x].sym == 'e' || \
			data->map->mapa[(int)tmp_img->y][(int)tmp_img->x].sym == '1')
			error_end(2);
		tmp_img = tmp_img->next;
	}
}

static void	calc_sprite_data(t_data_mlx *data, t_spr_tex *img)
{
	img->x_ray = img->x - data->map->play.x;
	img->y_ray = img->y - data->map->play.y;
	img->t_x = data->am_s->inv * (data->map->play.dir_y * \
		img->x_ray - data->map->play.dir_x * img->y_ray);
	img->t_y = data->am_s->inv * (-data->map->cam.pl_y * \
		img->x_ray + data->map->cam.pl_x * img->y_ray);
	img->pos_spr_x = (int)((WIDTH / 2) * (1 + img->t_x / img->t_y));
	img->h_spr = abs((int)(HEIGHT / img->t_y));
	img->dr_st_y = -(img->h_spr / 2) + HEIGHT / 2;
	if (img->dr_st_y + data->map->cam.vertilcal_pos < 0)
		img->dr_st_y = -data->map->cam.vertilcal_pos;
	img->dr_f_y = img->h_spr / 2 + HEIGHT / 2;
	if (img->dr_f_y > HEIGHT - data->map->cam.vertilcal_pos)
		img->dr_f_y = HEIGHT - data->map->cam.vertilcal_pos - 1;
	img->w_spr = abs((int)(HEIGHT / img->t_y));
	img->dr_st_x = -img->w_spr / 2 + img->pos_spr_x;
	if (img->dr_st_x < 0)
		img->dr_st_x = 0;
	img->dr_f_x = img->w_spr / 2 + img->pos_spr_x;
	if (img->dr_f_x >= WIDTH)
		img->dr_f_x = WIDTH - 1;
}

static void	draw_sprite_data(t_data_mlx *data, t_spr_tex *img, \
	t_cost_tex *cost, int i)
{
	int				j;
	unsigned int	col;

	j = img->dr_st_y - 1;
	while (++j < img->dr_f_y)
	{
		img->d = j * 256 - HEIGHT * 128 + img->h_spr * 128;
		img->tex_y = (((img->d * cost[img->c_i].img_h) \
		/ img->h_spr) / 256);
		col = my_mlx_get_pixel(cost[img->c_i], img->tex_x, \
				img->tex_y);
		if (col != 0xFF000000)
			my_mlx_pixel_put(data, i, j + \
			data->map->cam.vertilcal_pos, col);
	}
}

void	draw_sprite(t_data_mlx *data, t_spr_tex *img, t_cost_tex *cost)
{
	int				i;
	int				f;

	calc_sprite_data(data, img);
	i = img->dr_st_x - 1;
	f = 0;
	img->fact_st_x = 0;
	img->fact_f_x = 0;
	while (++i < img->dr_f_x)
	{
		img->tex_x = ((int)(256 * (i - (-img->w_spr / 2 + \
		img->pos_spr_x)) * cost[img->c_i].img_w / img->w_spr) / 256);
		if (img->t_y > 0 && i > 0 && i < WIDTH && \
			img->t_y < data->sector[i])
		{
			if (!f)
			{
				img->fact_st_x = i;
				f = 1;
			}
			img->fact_f_x = i;
			draw_sprite_data(data, img, cost, i);
		}
	}
}
