/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:35 by utygett           #+#    #+#             */
/*   Updated: 2022/03/17 11:21:02 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	ft_mouse(int keycode, int x, int y, t_data_mlx *data)
{	
	if (keycode == MOUSE_RIGHT_KEY)
		data->mouse_code[keycode] = PRESS;
	printf("mouse code : %d\n", keycode);
	return (0);
}
