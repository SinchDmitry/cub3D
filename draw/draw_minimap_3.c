/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:35 by utygett           #+#    #+#             */
/*   Updated: 2022/03/31 18:38:00 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	in_circle(float x, float y, int r)
{
	float	distance;

	distance = sqrtf(powf(x - MOVEX, 2.0f) + powf(y - MOVEY, 2.0f));
	if (distance <= r)
	{
		if ((r - distance) < 1.0f)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_board(t_data_mlx *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAPHEIGHT)
	{
		j = 0;
		while (j < MINIMAPWIDTH)
		{	
			if (!in_circle(j, i, 100))
				my_mlx_pixel_put(data, i, j, INVISIBLE_COL);
			if (in_circle(j, i, 100) == 2)
				my_mlx_pixel_put(data, i, j, WHITE_COL);
			if (in_circle(j, i, MMTEXSIZE / 4) == 1)
				my_mlx_pixel_put(data, i, j, WHITE_COL);
			j++;
		}
		i++;
	}
}
