/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:47 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 00:05:43 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../cub.h"

# define RGB 		101
# define TEXTURE 	102
# define SPRITE 	103
# define FLOOR 		111
# define SKY 		112
# define NORTH 		113
# define SOUTH 		114
# define EAST 		115
# define WEST 		116
# define AMONG 		117
# define COMP 		118
# define DOOR 		119
# define FOV		1.571f

/* general */
void	map_info(t_data_mlx *data, char **map_str);
int		param_map(t_data_mlx *data, char **map_str);
void	map_create(t_data_mlx *data, char **map_str);
int		key_compare(t_data_mlx *data, char **arg, char *map_str);

/* utils */
int		ft_iscompas(t_map_info *map, char ch, int *first_in);
int		create_trgb(int t, int r, int g, int b);
void	add_back_or_new(t_spr_tex **img, int size, int x, int y);
void	neighbor(t_map_info *map, int i, int j);

/* objects */
void	objects_parse(t_data_mlx *data, char *arg, int val);

#endif