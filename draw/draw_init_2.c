/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/23 11:57:28 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_wall(t_data_mlx *data)
{
	data->wall[0].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall0.xpm", &data->wall[0].img_h, &data->wall[0].img_w);
	data->wall[0].addr = mlx_get_data_addr(data->wall[0].img, \
		&data->wall[0].bits_per_pixel, &data->wall[0].line_length, \
		&data->wall[0].endian);
	data->wall[1].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall1.xpm", &data->wall[1].img_h, &data->wall[1].img_w);
	data->wall[1].addr = mlx_get_data_addr(data->wall[1].img, \
		&data->wall[1].bits_per_pixel, &data->wall[1].line_length, \
		&data->wall[1].endian);
	data->wall[2].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall2.xpm", &data->wall[2].img_h, &data->wall[2].img_w);
	data->wall[2].addr = mlx_get_data_addr(data->wall[2].img, \
		&data->wall[2].bits_per_pixel, &data->wall[2].line_length, \
		&data->wall[2].endian);
	data->wall[3].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall3.xpm", &data->wall[3].img_h, &data->wall[3].img_w);
	data->wall[3].addr = mlx_get_data_addr(data->wall[3].img, \
		&data->wall[3].bits_per_pixel, &data->wall[3].line_length, \
		&data->wall[3].endian);
}

static void	init_map_gun(t_data_mlx *data)
{
	int		img_h;
	int		img_w;

	data->weapon.img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/blaster1.xpm", &data->weapon.img_w, &data->weapon.img_h);
	data->weapon.addr = mlx_get_data_addr(data->weapon.img, \
		&data->weapon.bits_per_pixel, &data->weapon.line_length, \
		&data->weapon.endian);
	data->image.compas = mlx_xpm_file_to_image(data->mlx, "./textures/N.xpm", \
		&img_h, &img_w);
}

static void	init_sprite_data(t_data_mlx *data)
{
	data->am_s->spr_img[0].x = 22.5;
	data->am_s->spr_img[0].y = 4.5;
	data->am_s->spr_img[1].x = 38.5;
	data->am_s->spr_img[1].y = 10.5;
	data->am_s->spr_img[2].x = 26.5;
	data->am_s->spr_img[2].y = 15.5;
	data->am_s->spr_img[3].y = 23.5;
	data->am_s->spr_img[3].x = 23.5;
	data->am_s->spr_img[0].dead = 0;
	data->am_s->spr_img[0].shot = 0;
	data->am_s->spr_img[1].dead = 0;
	data->am_s->spr_img[1].shot = 0;
	data->am_s->spr_img[2].dead = 0;
	data->am_s->spr_img[2].shot = 0;
	data->am_s->spr_img[3].dead = 0;
	data->am_s->spr_img[3].shot = 0;
	data->am_s->comp_img.x = 11;
	data->am_s->comp_img.y = 11;
	data->am_s->comp_img.shot = 0;
}

void	init_images(t_data_mlx *data)
{
	char	xpm_path[1024];

	data->am_s = malloc(sizeof(t_spr));
	if (!data->am_s)
		error_end(3);
	save_point(data->am_s, P_FRONT);
	init_sprites(data);
	init_wall(data);
	init_map_gun(data);
	init_sprite_data(data);
}
