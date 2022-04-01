/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/01 21:11:54 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/*
void	laser_width(t_data_mlx *data, t_vls *bullet, int width_step)
{
	bullet->x1 = 40 + (WIDTH / 2 + WIDTH / 20) + width_step;
	bullet->y1 = 40 + (HEIGHT - data->weapon.img_h);
	bullet->x2 = WIDTH / 2 + width_step;
	bullet->y2 = HEIGHT / 2;
}
*/

void	action_among(t_data_mlx *data, t_spr_tex *img, int flag)
{
	int		left_x;
	int		right_x;
	int		tmp_x;
	int		tmp_y;

	tmp_x = img->dr_st_x + (img->dr_f_x - img->dr_st_x) / 3;
	if (flag == FULL_SIZE)
		tmp_x = img->dr_st_x;
	left_x = tmp_x;
	if (img->fact_st_x > tmp_x)
		left_x = img->fact_st_x;
	tmp_x = img->dr_f_x - (img->dr_f_x - img->dr_st_x) / 3;
	if (flag == FULL_SIZE)
		tmp_x = img->dr_f_x;
	right_x = tmp_x;
	if (img->fact_f_x < tmp_x)
		right_x = img->fact_f_x;
	tmp_y = img->dr_st_y + (img->dr_f_y - img->dr_st_y) / 2;
	if (flag == FULL_SIZE)
		tmp_y = img->dr_f_y;
	if (WIDTH / 2 > left_x && WIDTH / 2 < right_x)
		if (HEIGHT / 2 > img->dr_st_y - data->map->cam.vertilcal_pos \
			&& HEIGHT / 2 < tmp_y - data->map->cam.vertilcal_pos)
				img->shot = 1;
}

/*
void	action_among(t_data_mlx *data, t_spr_tex *img, int spr_numm, int flag)
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
*/

void	attack_weapon(t_data_mlx *data, t_spr_tex *img, int size)
{
	t_vls	bullet;
	int		i;

	i = LASER_WIDTH;
	while (i >= 0)
	{
		// laser_width(data, &bullet, i--);
		bullet.x1 = 40 + (WIDTH / 2 + WIDTH / 20) + i;
		bullet.y1 = 40 + (HEIGHT - data->am_s->weapon_textures->img_h);
		bullet.x2 = WIDTH / 2 + i;
		bullet.y2 = HEIGHT / 2;
		i--;
		draw_line(data, bullet, RED_COL);
	}
	action_among(data, img, size);
	// action_among(data, img, spr_n, size);
}

/*
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
*/

static void	calc_sprite_data(t_data_mlx *data, t_spr_tex *img)
{
	// static void	init_ray_param(t_data_mlx *data, t_spr_tex *img)
	img->x_ray = img->x - data->map->play.x;
	img->y_ray = img->y - data->map->play.y;
	// static void	calc_sprite_param(t_data_mlx *data, t_spr_tex *img)
	img->t_x = data->am_s->inv * (data->map->play.dir_y * \
		img->x_ray - data->map->play.dir_x * img->y_ray);
	img->t_y = data->am_s->inv * (-data->map->cam.pl_y * \
		img->x_ray + data->map->cam.pl_x * img->y_ray);
	img->pos_spr_x = (int)((WIDTH / 2) * (1 + img->t_x / img->t_y));
	img->h_spr = abs((int)(HEIGHT / img->t_y));
	img->dr_st_y = -(img->h_spr / 2) + HEIGHT / 2;
	// static void	calc_sprite_sector(t_data_mlx *data, t_spr_tex *img)
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

/*
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
*/

/*
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
*/

void	draw_sprite(t_data_mlx *data, t_spr_tex *img, t_cost_tex* costumes)
{
	int	i;
	int	j;
	int	f;

	calc_sprite_data(data, img);
	i = img->dr_st_x - 1;
	f = 0;
	img->fact_st_x = 0;
	img->fact_f_x = 0;
	while (++i < img->dr_f_x)
	{
		img->tex_x = ((int)(256 * (i - (-img->w_spr / 2 + \
		img->pos_spr_x)) * costumes[img->c_i].img_w / img->w_spr) / 256);
		if (img->t_y > 0 && i > 0 && i < WIDTH && \
			img->t_y < data->sector[i])
		{
			if (!f)
			{
				img->fact_st_x = i;
				f = 1;
			}
			img->fact_f_x = i;
			j = img->dr_st_y - 1;
			while (++j < img->dr_f_y)
			{
				img->d = j * 256 - HEIGHT * 128 + img->h_spr * 128;
				img->tex_y = (((img->d * costumes[img->c_i].img_h) \
				/ img->h_spr) / 256);
				my_mlx_pixel_put(data, i, j + data->map->cam.vertilcal_pos, \
					my_mlx_get_pixel(costumes[img->c_i], img->tex_x, \
						img->tex_y));
			}
		}
	}
}

/*
void	draw_sprite(t_data_mlx *data, t_spr_tex *img, int n, int cost)
{
	int	i;
	int	j;
	int	f;

	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
	init_ray_param(data, img);
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
*/

void	check_costume(t_data_mlx *data, t_spr_tex *img, t_cost_tex* costumes, \
	int num_of_cost)
{
	t_spr_tex	*tmp_img;

	tmp_img = img;
	data->am_s->inv = 1.0 / (data->map->cam.pl_x * data->map->play.dir_y - \
		data->map->play.dir_x * data->map->cam.pl_y);
	while (tmp_img)
	{	
		if (tmp_img->shot && !tmp_img->dead)
		{
			++tmp_img->c_i;
			if (tmp_img->c_i == num_of_cost - 1)
				tmp_img->dead = 1;
		}
		// if (!tmp_img->dead)
		//	draw_sprite(data, tmp_img, costumes, tmp_img->c_i);
		draw_sprite(data, tmp_img, costumes);
		// else
		// 	draw_sprite(data, tmp_img, costumes, num_of_cost - 1);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, tmp_img, AMONG_SIZE);
		tmp_img = tmp_img->next;
	}
}

/*
void	check_costume(t_data_mlx *data, t_spr_tex *img, int num_of_cost)
{
	static int	i[SPR_NUM];
	int			spr_n;

	spr_n = 0;
	while (spr_n < img[0].num_of_spr)
	{
		if (img[spr_n].shot && !img[spr_n].dead)
		{
			++i[spr_n];
			if (i[spr_n] == num_of_cost - 1)
				img[spr_n].dead = 1;
		}
		img[spr_n].c_num = i[spr_n];
		if (!img[spr_n].dead)
			draw_sprite(data, img, spr_n, img[spr_n].c_num);
		else
			draw_sprite(data, img, spr_n, num_of_cost - 1);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, img, spr_n, AMONG_SIZE);
		spr_n++;
	}
}
*/

/*
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
*/

// void	check_door(t_data_mlx *data, t_spr_tex *img)
// {
// 	static int	i[DOOR_NUM];
// 	int			spr_n;

// 	spr_n = 0;
// 	while (spr_n < img[0].num_of_spr)
// 	{
// 		if (img[spr_n].shot && !img[spr_n].dead)
// 		{
// 			++i[spr_n];
// 			if (i[spr_n] == img[0].num_of_cost - 1)
// 				img[spr_n].dead = 1;
// 		}
// 		img[spr_n].c_num = i[spr_n];
// 		if (!img[spr_n].dead)
// 			draw_door_sprite(data, img, spr_n, img[spr_n].c_num);
// 		else
// 			draw_door_sprite(data, img, spr_n, img[0].num_of_cost - 1);
// 		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
// 			attack_weapon(data, img, spr_n, FULL_SIZE);
// 		spr_n++;
// 	}
// }

void	check_computer(t_data_mlx *data)
{
	static int	i;
	static int	j;

	if (data->am_s->comp_img->shot)
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
	data->am_s->comp_img->c_i = i;
	draw_sprite(data, data->am_s->comp_img, data->am_s->comp_costumes);
	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
		attack_weapon(data, data->am_s->comp_img, FULL_SIZE);
}

/*
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
*/

void	draw_objects(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	draw_invis_background(data, WIDTH, HEIGHT);
	check_costume(data, data->am_s->spr_img, data->am_s->am_costumes, \
		SPR_COSTUME);
	check_computer(data);
	check_door(data);
	draw_aim(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
