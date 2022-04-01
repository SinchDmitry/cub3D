/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/01 19:27:30 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_sprite(t_data_mlx *data, t_cost_tex *img, char *dir, \
	int num_of_c)
{
	int		i;
	char	*img_num;
	char	xpm_path[1024];

	i = -1;
	while (++i < num_of_c)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);
		img[i].img = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img[i].img_h, &img[i].img_w);
		img[i].addr = mlx_get_data_addr(img[i].img, \
			&img[i].bits_per_pixel, &img[i].line_length, &img[i].endian);
	}
}

/*
static void	init_space(t_data_mlx *data, char *xpm_path) // make union with init_sprite function 
{
	int		i;
	int		img_h;
	int		img_w;
	char	*img_num;
	char	*space_dir;

	i = -1;
	space_dir = "./textures/space_fly/space2/space_fly";
	while (++i < 40)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, space_dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);
		data->image.mm_space[i] = \
			mlx_xpm_file_to_image(data->mlx, xpm_path, &img_h, &img_w);
	}
}
*/

static void	init_sprites(t_data_mlx *data)
{
	t_ref	t;

	t.space_dir = "./textures/space_fly/space2/space_fly";
	t.wall_dir = "./textures/wall";
	t.among_dir = "./textures/among/0";
	t.comp_dir = "./textures/rick/";
	t.weapon_dir = "./textures/blaster";
	t.door_dir = "./textures/door/door";
	t.compas_dir = "./textures/N";
	init_sprite(data, data->am_s->wall_textures, t.wall_dir, WALL_TEXTURE);
	init_sprite(data, data->am_s->am_costumes, t.among_dir, SPR_COSTUME);
	init_sprite(data, data->am_s->comp_costumes, t.comp_dir, COMP_COSTUME);
	init_sprite(data, data->am_s->space_textures, t.space_dir, SPACE_TEXTURE);
	init_sprite(data, data->am_s->door_textures, t.door_dir, DOOR_TEXTURE);
	init_sprite(data, data->am_s->weapon_textures, t.weapon_dir, WEAP_TEXTURE);
	init_sprite(data, data->am_s->compas_textures, t.compas_dir, CMPS_TEXTURE);
	// init_space(data, xpm_path);
	// init_sprite(data, &data->am_s->wall_textures, t.weapon_dir, 1);
	// init_sprite(data, &data->am_s->wall_textures, t.compas_dir, 1);
}

void	init_images(t_data_mlx *data)
{
	// char	xpm_path[1024];

	// if (!data->am_s)
	// 	error_end(3);
	// save_point(data->am_s, P_FRONT);
	// *data->am_s = (t_data_tex){};
	data->wall_img = ft_calloc_error_end(sizeof(t_wall_tex), 1, P_FRONT);
	// if (!data->wall_img)
	// 	error_end(3);
	// *data->wall_img = (t_wall_tex){};
	// save_point(data->wall_img, P_FRONT);
	init_sprites(data);
	// init_wall(data, data->wall_img);
	// init_map_gun(data);
}

/*
static void	init_wall(t_data_mlx *data, t_wall_tex *img) // make union with init_sprite function 
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

static void	init_map_gun(t_data_mlx *data) // make union with init_sprite function 
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
*/