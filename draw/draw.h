/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/02/17 16:26:56 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../cub.h"
#define WIDTH 2000
#define HEIGHT 2000
#define PLAYERCOL 0x00FFFFFF
#define WALLCOL 0x0000FFFF
#define FLOORCOL 0x000000FF
#define TEXTURESIZE 32

typedef struct	s_player {
	float x;
	float y;
}				t_player;

typedef struct	s_data_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_info  *map;
	t_player player;
}				t_data_mlx;

