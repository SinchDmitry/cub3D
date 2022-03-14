/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:35 by utygett           #+#    #+#             */
/*   Updated: 2022/03/13 15:21:55 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	ft_mouse(int keycode, int x, int y, t_data_mlx *data)
{
	data->mouse_x = x;
	data->mouse_y = y;
	printf("button : %d x : %d y : %d\n", keycode, x, y);
	return (0);
}
