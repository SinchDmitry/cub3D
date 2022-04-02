/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 16:33:36 by utygett          ###   ########.fr       */
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
			&img[i].img_w, &img[i].img_h);
		img[i].addr = mlx_get_data_addr(img[i].img, \
			&img[i].bits_per_pixel, &img[i].line_length, &img[i].endian);
	}
}

static void	init_doors(t_data_mlx *data)
{
	t_spr_tex	*tmp_img;
	tmp_img = data->am_s->door_img;
	while (tmp_img)
	{	
		data->map->mapa[(int)tmp_img->x][(int)tmp_img->y].door = 1;
		data->map->mapa[(int)tmp_img->x][(int)tmp_img->y].door_state = 0;
		tmp_img = tmp_img->next;
	}
}

void	init_sprites(t_data_mlx *data)
{
	t_ref	t;

	t.space_dir = "./textures/space_fly/space2/space_fly";
	t.wall_dir = "./textures/wall";
	t.among_dir = "./textures/among/0";
	t.comp_dir = "./textures/rick/";
	t.weapon_dir = "./textures/blaster";
	t.door_dir = "./textures/door/door";
	t.compas_dir = "./textures/N";
	init_sprite(data, data->am_s->wall_tex, t.wall_dir, WALL_TEXTURE);
	init_sprite(data, data->am_s->am_costumes, t.among_dir, SPR_COSTUME);
	init_sprite(data, data->am_s->comp_costumes, t.comp_dir, COMP_COSTUME);
	init_sprite(data, data->am_s->space_textures, t.space_dir, SPACE_TEXTURE);
	init_sprite(data, data->am_s->door_tex, t.door_dir, DOOR_TEXTURE);
	init_sprite(data, data->am_s->weapon_textures, t.weapon_dir, WEAP_TEXTURE);
	init_sprite(data, data->am_s->compas_textures, t.compas_dir, CMPS_TEXTURE);
	init_doors(data);
}
