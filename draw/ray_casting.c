/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 17:05:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/20 17:30:37 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void ray_analys(int c)
{
	int	x;
	int y; 
	int	i;
	int k;

	x = -1;
	k = 1;
	while (++x < WIDTH)
	{
		i = 0;
		y = HEIGHT - c * k;
		while (i++ <  WIDTH / ((FOV - ANG_START) / ANG_STEP))
			ray_draw(x, y);	
	}
}