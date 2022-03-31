/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:24:09 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/31 18:20:28 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_iscompas(t_map_info *map, char ch, int *first_in)
{
	if (ch == 'S' || ch == 'N' || ch == 'W' || ch == 'E')
	{
		if (*first_in)
			error_end(2);
		select_dir(map, ch);
		*first_in += 1;
		return (1);
	}
	else
		return (0);
}

/* front or back ? */
void	add_back_or_new(t_spr_tex **img, int size, int x, int y)
{
	t_spr_tex	*last;
	t_spr_tex	*new;

	last = *img;
	new = ft_calloc_error_end(sizeof(t_spr_tex), 1, P_FRONT);
	new->x = x;
	new->y = y;
	new->size = size;
	if (!(*img))
		*img = new;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	neighbor(t_map_info *map, int i, int j)
{
	if (i > 0)
		if (map->mapa[i - 1][j].sym == '0')
			error_end(2);
	if (i < map->height - 1)
		if (map->mapa[i + 1][j].sym == '0')
			error_end(2);
	if (j > 0)
		if (map->mapa[i][j - 1].sym == '0')
			error_end(2);
	if (j < map->width - 1)
		if (map->mapa[i][j + 1].sym == '0')
			error_end(2);
}
