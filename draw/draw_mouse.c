/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:35 by utygett           #+#    #+#             */
/*   Updated: 2022/03/14 21:24:21 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	ft_mouse(int keycode, int x, int y, t_data_mlx *data)
{
	data->mouse_x = x; 
	data->mouse_y = y;	
	return (0);
}