/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:50:19 by utygett           #+#    #+#             */
/*   Updated: 2022/03/31 18:38:24 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	image_put_map_move(int x, int y, t_data_mlx *data, int num)
{
	float	x1;
	float	y1;
	float	h;
	float	w;

	x1 = x;
	y1 = y;
	h = ((data->map->play.x) * MMTEXSIZE);
	w = ((data->map->play.y) * MMTEXSIZE);
	x = ((x1 - h) * sin(data->map->play.a + ROTATE_MOV) - (y1 - w) * \
		cos(data->map->play.a + ROTATE_MOV));
	y = ((x1 - h) * cos(data->map->play.a + ROTATE_MOV) + (y1 - w) * \
		sin(data->map->play.a + ROTATE_MOV));
	if (x + MOVEX < MINIMAPHEIGHT && y + MOVEY < MINIMAPWIDTH && \
		x + MOVEX > 0 && y + MOVEY > 0)
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.compas, x + MOVEX - 4, y + MOVEY - 4);
}

// void	draw_invis_square(int x, int y, t_data_mlx *data, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (x + i < x + MMTEXSIZE)
// 	{
// 		j = 0;
// 		while (y + j < y + MMTEXSIZE)
// 		{	
// 			my_mlx_pixel_put(data, y, x, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

static void	mimimap_sym(t_data_mlx *data)
{
	float	c;
	float	ray_x;
	float	ray_y;

	c = 0;
	while (c < MMTEXSIZE / 4)
	{
		ray_x = data->map->play.x + c * cos(4.71f);
		ray_y = data->map->play.y + c * sin(4.71f);
		ray_x *= MMTEXSIZE;
		ray_y *= MMTEXSIZE;
		c = c + 0.1f;
	}
	image_put_map_move(ray_x, ray_y, data, 0);
}

void	draw_minimap(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	draw_map_with_move(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mimimap_sym(data);
	mlx_destroy_image(data->mlx, data->img);
}
