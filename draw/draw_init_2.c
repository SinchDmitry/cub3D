/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/25 21:48:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_wall(t_data_mlx *data, t_wall_tex *img)
{
	img->wall[0].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall0.xpm", &img->wall[0].img_h, &img->wall[0].img_w);
	img->wall[0].addr = mlx_get_data_addr(img->wall[0].img, \
		&img->wall[0].bits_per_pixel, \
		&img->wall[0].line_length, &img->wall[0].endian);
	img->wall[1].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall1.xpm", &img->wall[1].img_h, &img->wall[1].img_w);
	img->wall[1].addr = mlx_get_data_addr(img->wall[1].img, \
		&img->wall[1].bits_per_pixel, \
		&img->wall[1].line_length, &img->wall[1].endian);
	img->wall[2].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall2.xpm", &img->wall[2].img_h, &img->wall[2].img_w);
	img->wall[2].addr = mlx_get_data_addr(img->wall[2].img, \
		&img->wall[2].bits_per_pixel, \
		&img->wall[2].line_length, &img->wall[2].endian);
	img->wall[3].img = mlx_xpm_file_to_image(data->mlx, \
		"./textures/wall3.xpm", &img->wall[3].img_h, &img->wall[3].img_w);
	img->wall[3].addr = mlx_get_data_addr(img->wall[3].img, \
		&img->wall[3].bits_per_pixel, \
		&img->wall[3].line_length, &img->wall[3].endian);
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
	data->am_s->spr_img[0].dead = 0;
	data->am_s->spr_img[0].shot = 0;
	data->am_s->spr_img[1].dead = 0;
	data->am_s->spr_img[1].shot = 0;
	data->am_s->spr_img[2].dead = 0;
	data->am_s->spr_img[2].shot = 0;
	data->am_s->spr_img[3].dead = 0;
	data->am_s->spr_img[3].shot = 0;
	data->am_s->comp_img.shot = 0;
	data->am_s->spr_img->size = AMONG_SIZE;
	data->am_s->spr_img->num_of_spr = SPR_NUM;
	data->am_s->spr_img->num_of_cost = SPR_COSTUME;
	data->am_s->comp_img.size = FULL_SIZE;
	data->am_s->comp_img.num_of_spr = 0;
	data->am_s->comp_img.num_of_cost = COMP_COSTUME;
	data->am_s->door_img[0].dead = 0;
	data->am_s->door_img[0].shot = 0;
	data->am_s->door_img[1].dead = 0;
	data->am_s->door_img[1].shot = 0;
	data->am_s->door_img[2].dead = 0;
	data->am_s->door_img[2].shot = 0;
	data->am_s->door_img[3].dead = 0;
	data->am_s->door_img->size = FULL_SIZE;
	data->am_s->door_img->num_of_spr = DOOR_NUM;
	data->am_s->door_img->num_of_cost = DOOR_COSTUME;
}

void	init_images(t_data_mlx *data)
{
	char	xpm_path[1024];

	data->am_s = malloc(sizeof(t_spr));
	if (!data->am_s)
		error_end(3);
	save_point(data->am_s, P_FRONT);
	data->wall_img = malloc(sizeof(t_wall_tex));
	if (!data->wall_img)
		error_end(3);
	save_point(data->wall_img, P_FRONT);
	init_sprite_data(data);
	init_sprites(data);
	init_wall(data, data->wall_img);
	init_map_gun(data);
}
