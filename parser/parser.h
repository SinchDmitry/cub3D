/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:47 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/26 21:16:39 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../cub.h"
// # include "../libft/libft.h"

# define RGB 		101
# define TEXTURE 	102
# define FLOOR 		111
# define SKY 		112
# define NORTH 		113
# define SOUTH 		114
# define EAST 		115
# define WEST 		116
# define FOV		1.571f
// # define BUFFER_SIZE 10000;

// struct						s_info;
// struct						s_texture;
// struct						s_rgb;
// typedef struct s_info		t_info;
// typedef struct s_texture	t_texture;
// typedef struct s_rgb		t_rgb;

t_info	*parser(int argc, char **argv, int fd);
void	map_info(t_info *map, char **map_str);
int		param_map(t_info *map, char **map_str);
void	map_struct(t_info *map, char **map_str);

#endif