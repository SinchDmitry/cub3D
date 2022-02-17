/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/02/17 19:26:52 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../cub.h"
#define WIDTH 1280
#define HEIGHT 720
#define MINIMAPWIDTH 350
#define MINIMAPHEIGHT 350
#define PLAYERCOL 0x00FFFFFF
#define WALLCOL 0x0000FFFF
#define FLOORCOL 0x000000FF
#define TEXTURESIZE 8
#define MOVE_SPEED 0.2

typedef struct	s_data_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_info  *map;
}				t_data_mlx;

