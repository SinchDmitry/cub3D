/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/02/17 20:01:50 by aarchiba         ###   ########.fr       */
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
#define RAYCOL 0x0000000F
#define TEXTURESIZE 8
#define MOVE_SPEED 0.2
#define MOVE_ANGLE 0.1
#define VIEW_RANGE 100
#define LEFT_KEY 123
#define RIGHT_KEY 124
#define DOWN_KEY 125
#define UP_KEY 126

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

