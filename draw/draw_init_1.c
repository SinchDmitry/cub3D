/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:26:13 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/24 18:20:25 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_all(t_data_mlx *data, t_spr_tex *img, int num, \
	int costume)
{
	int		i;
	int		j;

	j = 0;
	while (++j < num)
	{
		i = -1;
		while (++i < costume)
		{
			img[j].costumes[i].img = img[0].costumes[i].img;
			img[j].costumes[i].addr = img[0].costumes[i].addr;
			img[j].costumes[i].img_h = img[0].costumes[i].img_h;
			img[j].costumes[i].img_w = img[0].costumes[i].img_w;
			img[j].costumes[i].bits_per_pixel = \
				img[0].costumes[i].bits_per_pixel;
			img[j].costumes[i].line_length = img[0].costumes[i].line_length;
			img[j].costumes[i].endian = img[0].costumes[i].endian;
		}
	}
}

static void	init_sprite(t_data_mlx *data, t_spr_tex *img, char *xpm_path, \
	char *dir)
{
	int		i;
	char	*img_num;

	i = -1;
	while (++i < img->num_of_cost)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);
		img[0].costumes[i].img = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img[0].costumes[i].img_h, \
			&img[0].costumes[i].img_w);
		img[0].costumes[i].addr = mlx_get_data_addr(img[0].costumes[i].img, \
			&img[0].costumes[i].bits_per_pixel, \
			&img[0].costumes[i].line_length, &img[0].costumes[i].endian);
	}
	init_all(data, img, img->num_of_spr, img->num_of_cost);
}

static void	init_space(t_data_mlx *data, char *xpm_path)
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

void	init_sprites(t_data_mlx *data)
{
	char	xpm_path[1024];

	init_space(data, xpm_path);
	init_sprite(data, data->am_s->spr_img, xpm_path, "./textures/among/0");
	init_sprite(data, &data->am_s->comp_img, xpm_path, "./textures/rick/");
	init_sprite(data, data->am_s->door_img, xpm_path, "./textures/door/door");
}
