/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:33:52 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/24 12:36:32 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

unsigned int	my_mlx_get_pixel(t_tex costume, int x, int y)
{	
	return (*(unsigned int *)(costume.addr + \
		(x * costume.bits_per_pixel / 8 + y * costume.line_length)));
}

void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	render_img(t_data_mlx *data)
{
	static int	i_space;

	if (!data->map->play.f_map)
	{	
		++i_space;
		if (i_space > 39)
			i_space = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i_space], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, \
			WIDTH / 2 - data->map->width * TEXSIZE / 2, \
			HEIGHT / 2 - data->map->height * TEXSIZE / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
}

int	render_next_frame(t_data_mlx *data)
{
	int			img_h;
	int			img_w;

	if (data->map->play.f_map)
	{
		draw_fvp(data);
		draw_objects(data);
		if (data->map->play.f_minimap)
			draw_minimap(data);
	}
	render_img(data);
	mouse_move(data);
	key_h(data);
	mlx_mouse_hide();
	return (0);
}
