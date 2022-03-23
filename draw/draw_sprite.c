/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/23 16:58:50 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	laser_width(t_data_mlx *data, t_vls *bullet, int width_step)
{
	bullet->x1 = 40 + (WIDTH / 2 + WIDTH / 20) + width_step;
	bullet->y1 = 40 + (HEIGHT - data->weapon.img_h);
	bullet->x2 = WIDTH / 2 + width_step;
	bullet->y2 = HEIGHT / 2;
}

void	action_among(t_data_mlx *data, t_spr_tex *img, int spr_n, int flag)
{
	int		left_x;
	int		right_x;
	int		tmp_x;
	int		tmp_y;

	tmp_x = img[spr_n].dr_st_x + (img[spr_n].dr_f_x - img[spr_n].dr_st_x) / 3;
	if (flag == FULL_SIZE)
		tmp_x = img[spr_n].dr_st_x;
	left_x = tmp_x;
	if (img[spr_n].fact_st_x > tmp_x)
		left_x = img[spr_n].fact_st_x;
	tmp_x = img[spr_n].dr_f_x - (img[spr_n].dr_f_x - img[spr_n].dr_st_x) / 3;
	if (flag == FULL_SIZE)
		tmp_x = img[spr_n].dr_f_x;
	right_x = tmp_x;
	if (img[spr_n].fact_f_x < tmp_x)
		right_x = img[spr_n].fact_f_x;
	tmp_y = img[spr_n].dr_st_y + (img[spr_n].dr_f_y - img[spr_n].dr_st_y) / 2;
	if (flag == FULL_SIZE)
		tmp_y = img[spr_n].dr_f_y;
	if (WIDTH / 2 > left_x && WIDTH / 2 < right_x)
		if (HEIGHT / 2 > img[spr_n].dr_st_y - data->map->cam.vertilcal_pos \
			&& HEIGHT / 2 < tmp_y - data->map->cam.vertilcal_pos)
				img[spr_n].shot = 1;
}

void	attack_weapon(t_data_mlx *data, t_spr_tex *img, int spr_n, int size)
{
	t_vls	bullet;
	int		i;

	i = LASER_WIDTH;
	while (i >= 0)
	{
		laser_width(data, &bullet, i--);
		draw_line(data, bullet, RED_COL);
	}
	action_among(data, img, spr_n, size);
}

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

void	check_costume(t_data_mlx *data, t_spr_tex *img)
{
	static int	i[SPR_NUM];
	int			spr_n;

	spr_n = 0;
	while (spr_n < img[0].num_of_spr)
	{
		if (img[spr_n].shot && !img[spr_n].dead)
		{
			++i[spr_n];
			if (i[spr_n] == img[0].num_of_cost - 1)
				img[spr_n].dead = 1;
		}
		img[spr_n].c_num = i[spr_n];
		if (!img[spr_n].dead)
			draw_sprite(data, img, spr_n, img[spr_n].c_num);
		else
			draw_sprite(data, img, spr_n, img[0].num_of_cost - 1);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, img, spr_n, AMONG_SIZE);
		spr_n++;
	}
}

void	check_door(t_data_mlx *data, t_spr_tex *img)
{
	static int	i[DOOR_NUM];
	int			spr_n;

	spr_n = 0;
	while (spr_n < img[0].num_of_spr)
	{
		if (img[spr_n].shot && !img[spr_n].dead)
		{
			++i[spr_n];
			if (i[spr_n] == img[0].num_of_cost - 1)
				img[spr_n].dead = 1;
		}
		img[spr_n].c_num = i[spr_n];
		if (!img[spr_n].dead)
			draw_sprite(data, img, spr_n, img[spr_n].c_num);
		else
			draw_sprite(data, img, spr_n, img[0].num_of_cost - 1);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, img, spr_n, FULL_SIZE);
		spr_n++;
	}
}

void	check_computer(t_data_mlx *data)
{
	static int	i;
	static int	j;

	if (data->am_s->comp_img.shot)
	{
		if (!j)
		{
			if (i == COMP_COSTUME - 1)
				i = 0;
			++i;
		}
		j++;
		if (j == 4)
			j = 0;
	}
	data->am_s->comp_img.c_num = i;
	draw_sprite(data, &data->am_s->comp_img, 0, data->am_s->comp_img.c_num);
	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
		attack_weapon(data, &data->am_s->comp_img, 0, FULL_SIZE);
}

void	draw_objects(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	draw_invis_background(data, WIDTH, HEIGHT);
	check_costume(data, data->am_s->spr_img);
	check_door(data, data->am_s->door_img); // + flag
	check_computer(data);
	// check_door(data);
	draw_aim(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
