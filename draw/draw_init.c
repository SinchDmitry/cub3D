/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/01 19:57:45 by aarchiba         ###   ########.fr       */
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
}

void	init_images(t_data_mlx *data)
{
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
