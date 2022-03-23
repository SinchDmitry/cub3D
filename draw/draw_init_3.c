/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_init_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:49:10 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/23 13:53:37 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	init_all_doors(t_data_mlx *data, t_spr_tex *img)
{
	int		i;
	int		j;

	j = 0;
	while (++j < DOOR_NUM)
	{
		i = 0;
		// while (++i < SPR_COSTUME)
		// {
			img[j].costumes[i].img = img[0].costumes[i].img;
			img[j].costumes[i].addr = img[0].costumes[i].addr;
			img[j].costumes[i].img_h = img[0].costumes[i].img_h;
			img[j].costumes[i].img_w = img[0].costumes[i].img_w;
			img[j].costumes[i].bits_per_pixel = \
				img[0].costumes[i].bits_per_pixel;
			img[j].costumes[i].line_length = img[0].costumes[i].line_length;
			img[j].costumes[i].endian = img[0].costumes[i].endian;
		// }
	}
}

static void	init_doors(t_data_mlx *data, t_spr_tex *img, char *xpm_path)
{
	int		i;
	char	*img_num;
	char	*door_dir;

	door_dir = "./textures/door.xpm";
	i = -1;
	// while (++i < SPR_COSTUME)
	// {
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, door_dir, 1023);
		// img_num = ft_itoa(i);
		// ft_strlcat(xpm_path, img_num, 1023);
		// free(img_num);
		// ft_strlcat(xpm_path, ".xpm", 1023);
		img[0].costumes[i].img = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img[0].costumes[i].img_h, \
			&img[0].costumes[i].img_w);
		img[0].costumes[i].addr = mlx_get_data_addr(img[0].costumes[i].img, \
			&img[0].costumes[i].bits_per_pixel, \
			&img[0].costumes[i].line_length, &img[0].costumes[i].endian);
	// }
	init_all_doors(data, data->am_s->spr_img);
}
