/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:09 by utygett           #+#    #+#             */
/*   Updated: 2022/03/31 18:33:20 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_invis_background(t_data_mlx *data, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			my_mlx_pixel_put(data, i, j, INVISIBLE_COL);
	}
}

/*
void	draw_invis_background(t_data_mlx *data, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{	
			my_mlx_pixel_put(data, i, j, INVISIBLE_COL);
			j++;
		}
		i++;
	}
}
*/

void	pixel_put_map_move(int x, int y, t_data_mlx *data, int color)
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
		my_mlx_pixel_put(data, x + MOVEX, y + MOVEY, color);
}
