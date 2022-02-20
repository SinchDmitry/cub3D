/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:05:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/20 18:06:15 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void ray_analys(t_data_mlx *data, int c)
{
	static int	x;
	int y; 
	int	i;
	int k;

	k = 1;
	i = 0;
	y = HEIGHT - c * k;
	while (i++ <  WIDTH / ((FOV - ANG_START) / ANG_STEP))
		ray_draw(x, y);
	if (x <= WIDTH)
		++x;
	else
		x = 0;
}