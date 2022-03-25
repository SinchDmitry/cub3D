/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:30 by utygett           #+#    #+#             */
/*   Updated: 2022/03/25 21:55:55 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// static void	calc_sprite_door_param(t_data_mlx *data, t_spr_tex *img, int num)
// {
// 	img[num].t_x = data->am_s->inv * (data->map->play.dir_y * \
// 		img[num].x_ray - data->map->play.dir_x * img[num].y_ray);
// 	img[num].t_y = data->am_s->inv * (-data->map->cam.pl_y * \
// 		img[num].x_ray + data->map->cam.pl_x * img[num].y_ray);
// 	img[num].pos_spr_x = (int)((WIDTH / 2) * (1 + \
// 		img[num].t_x / img[num].t_y));
// 	// img[num].pos_spr_x = (int)((WIDTH / 2); 
// 	img[num].h_spr = abs((int)(HEIGHT / img[num].t_y));
// 	img[num].dr_st_y = -(img[num].h_spr / 2) + HEIGHT / 2;
// }

// static void	calc_sprite_door_sector(t_data_mlx *data, t_spr_tex *img, int num)
// {
// 	if (img[num].dr_st_y + data->map->cam.vertilcal_pos < 0)
// 		img[num].dr_st_y = -data->map->cam.vertilcal_pos;
// 	img[num].dr_f_y = img[num].h_spr / 2 + HEIGHT / 2;
// 	if (img[num].dr_f_y > HEIGHT - data->map->cam.vertilcal_pos)
// 		img[num].dr_f_y = HEIGHT - data->map->cam.vertilcal_pos - 1;
// 	img[num].w_spr = abs((int)(HEIGHT / img[num].t_y));
// 	img[num].dr_st_x = -img[num].w_spr / 2 + \
// 		img[num].pos_spr_x;
// 	if (img[num].dr_st_x < 0)
// 		img[num].dr_st_x = 0;
// 	img[num].dr_f_x = img[num].w_spr / 2 + \
// 		img[num].pos_spr_x;
// 	if (img[num].dr_f_x >= WIDTH)
// 		img[num].dr_f_x = WIDTH - 1;

// 	if(num == 1)
// 	{	
// 		printf("start : %d = img[num].w_spr(%d)/2+img[num].pos_spr_x(%d)\n", img[num].dr_st_x, -img[num].w_spr, img[num].pos_spr_x);
// 		printf("img[num].w_spr(%d) = 700 / img[num].t_y(%f)\n", img[num].w_spr, img[num].t_y);
// 		printf("img[num].pos_spr_x(%d = (int)((1000 / 2) * (1 +img[num].t_x(%f) / img[num].t_y(%f))\n", img[num].pos_spr_x, img[num].t_x, img[num].t_y);//
// 	}
// }


// static void	init_ray_door_param(t_data_mlx *data)
// {
// 	data->am_s->door_img[0].x_ray = data->am_s->door_img[0].x - data->map->play.x;
// 	data->am_s->door_img[0].y_ray = data->am_s->door_img[0].y - data->map->play.y;
// 	data->am_s->door_img[1].x_ray = data->am_s->door_img[1].x - data->map->play.x;
// 	data->am_s->door_img[1].y_ray = data->am_s->door_img[1].y - data->map->play.y;
// 	data->am_s->door_img[2].x_ray = data->am_s->door_img[2].x - data->map->play.x;
// 	data->am_s->door_img[2].y_ray = data->am_s->door_img[2].y - data->map->play.y;
// 	data->am_s->door_img[3].x_ray = data->am_s->door_img[3].x - data->map->play.x;
// 	data->am_s->door_img[3].y_ray = data->am_s->door_img[3].y - data->map->play.y;
// 	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
// 		data->map->play.dir_x * data->map->cam.pl_y);
// }

// void	draw_door_sprite(t_data_mlx *data, t_spr_tex *img, int n, int cost)
// {
// 	int	i;
// 	int	j;
// 	int	f;

// 	init_ray_door_param(data);
// 	calc_sprite_door_param(data, img, n);
// 	calc_sprite_door_sector(data, img, n);
// 	i = img[n].dr_st_x - 1;
// 	f = 0;
// 	// if(n == 1)
// 	// 	printf(" i : %d dr_f_x : %d num : %d\n", i, img[n].dr_f_x, n);
// 	img[n].fact_st_x = 0;
// 	img[n].fact_f_x = 0;
// 	while (++i < img[n].dr_f_x)
// 	{
// 		img[n].tex_x = ((int)(256 * (i - (-img[n].w_spr / 2 + \
// 		img[n].pos_spr_x)) * img[n].costumes[cost].img_w / img[n].w_spr) / 256);
// 		if (img[n].t_y > 0 && i > 0 && i < WIDTH && \
// 			img[n].t_y < data->sector[i])
// 		{
// 			if (!f)
// 			{
// 				img[n].fact_st_x = i;
// 				f = 1;
// 			}
// 			img[n].fact_f_x = i;
// 			j = img[n].dr_st_y - 1;
// 			while (++j < img[n].dr_f_y)
// 			{
// 				img[n].d = j * 256 - HEIGHT * 128 + img[n].h_spr * 128;
// 				img[n].tex_y = (((img[n].d * img[n].costumes[cost].img_h) \
// 				/ img[n].h_spr) / 256);
// 				my_mlx_pixel_put(data, i, j + data->map->cam.vertilcal_pos, \
// 					my_mlx_get_pixel(img[n].costumes[cost], img[n].tex_x, \
// 						img[n].tex_y));
// 			}
// 		}
// 	}
// }

void			draw_door(t_data_mlx *data)
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
					(data->am_s->door_img[0].costumes[0].img_h - 1);
				data->door_struct[x].tex_pos += data->door_struct[x].step;
				
				my_mlx_pixel_put(data, x, data->door_struct[x].start, my_mlx_get_pixel(data->am_s->door_img[0].costumes[0], \
					data->door_struct[x].text_x, data->door_struct[x].text_y));
			}
			data->door_struct[x].use = 0;
		}
	}
}

static void	ray_door_side(t_data_mlx *data, t_wall_tex *img, int x)
{
	if (x == WIDTH / 2)
		data->map->play.side_for_move = img->sym;
	img->tex_x = (int)(img->wall_x * (double)img->wall[img->sym].img_w);
	img->tex_x = img->wall[img->sym].img_w - img->tex_x - 1;
	img->step = 1.0 * img->wall[img->sym].img_w / img->line_height;
	img->tex_pos = (img->draw_start - data->map->cam.vertilcal_pos - \
		HEIGHT / 2 + img->line_height / 2) * img->step;
}

void init_door_pixels(t_data_mlx *data, int x)
{
	if (data->map->cam.wall_dir)
		data->sector[x] = (data->map->cam.side_dist_y - \
			data->map->cam.delta_dir_y);
	else
		data->sector[x] = (data->map->cam.side_dist_x - \
			data->map->cam.delta_dir_x);
	data->wall_img->line_height = (int)(HEIGHT / data->sector[x]);

	
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
	ray_door_side(data, data->wall_img, x);
	int	i;
	i = data->wall_img->draw_start - 1;
	data->door_struct[x].start = i;
	data->door_struct[x].use = 1;
	data->door_struct[x].end = data->wall_img->draw_end;
	data->door_struct[x].text_x = data->wall_img->tex_x;
	data->door_struct[x].step = data->wall_img->step;
	data->door_struct[x].tex_pos = data->wall_img->tex_pos;

	// i = data->wall_img->draw_start - 1;
	// while (++i < data->wall_img->draw_end)
	// {
	// 	data->wall_img->tex_y = (int)data->wall_img->tex_pos & \
	// 		(data->wall_img->wall[data->wall_img->sym].img_h - 1);
	// 	data->wall_img->tex_pos += data->wall_img->step;
	// 	data->wall_img->col = \
	// 		my_mlx_get_pixel(data->wall_img->wall[data->wall_img->sym], \
	// 		data->wall_img->tex_x, data->wall_img->tex_y);
	// 	my_mlx_pixel_put(data, x, i, data->wall_img->col);
	// }
	
}