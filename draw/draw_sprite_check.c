/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:06 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 17:35:04 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	action_among(t_data_mlx *data, t_spr_tex *img, int flag)
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

static void	attack_weapon(t_data_mlx *data, t_spr_tex *img, int size)
{
	t_vls	bullet;
	int		i;

	i = LASER_WIDTH;
	while (i >= 0)
	{
		bullet.x1 = 40 + WIDTH - data->am_s->weapon_textures->img_w - \
			WIDTH / 11 + i;
		bullet.y1 = 40 + (HEIGHT - data->am_s->weapon_textures->img_h);
		bullet.x2 = WIDTH / 2 + i;
		bullet.y2 = HEIGHT / 2;
		i--;
		draw_line(data, bullet, RED_COL);
	}
	if (img)
		action_among(data, img, size);
}

static void	check_costume(t_data_mlx *data, t_spr_tex *img, \
	t_cost_tex *cost, int num_of_cost)
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
		draw_sprite(data, tmp_img, cost);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, tmp_img, AMONG_SIZE);
		tmp_img = tmp_img->next;
	}
}

static void	check_computer(t_data_mlx *data)
{
	static int	j;
	t_spr_tex	*tmp_img;

	tmp_img = data->am_s->comp_img;
	while (tmp_img)
	{
		if (tmp_img->shot)
		{
			if (!j)
			{
				if (tmp_img->c_i == COMP_COSTUME - 1)
					tmp_img->c_i = 0;
				++tmp_img->c_i;
			}
			j++;
			if (j == 4)
				j = 0;
		}
		draw_sprite(data, tmp_img, data->am_s->comp_cost);
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			attack_weapon(data, tmp_img, FULL_SIZE);
		tmp_img = tmp_img->next;
	}
}

void	draw_objects(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	draw_invis_background(data, WIDTH, HEIGHT);
	check_costume(data, data->am_s->spr_img, data->am_s->am_cost, \
		SPR_COSTUME);
	check_computer(data);
	check_door(data);
	draw_aim(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
