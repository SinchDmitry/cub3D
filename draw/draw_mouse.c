/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:35 by utygett           #+#    #+#             */
/*   Updated: 2022/03/17 17:54:25 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	ft_mouse(int keycode, int x, int y, t_data_mlx *data)
{	
	if (keycode == MOUSE_LEFT_KEY)
		data->mouse_code[keycode] = PRESS;
	// printf("mouse code : %d\n", keycode);
	return (0);
}
