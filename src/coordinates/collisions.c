/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:48:37 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/07 17:26:17 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	wall_in_the_way_hori(t_map *map, int new_cx, int new_cy);
bool	wall_in_the_way_vert(t_map *map, int new_cx, int new_cy);

// static bool	is_wall(char c);

/*
Function to check if there is a wall in the way of the player's movement
  - The next coordinates of the player circle is checked with respect to its
    center and diameter, against the img_array
  - The player blob is treated as a rectangle to check for colliding coordinates
  - The function returns true if the resulting coordinates after the applied
	movement overlap with the wall coordinates in the map i.e. values 1

*/
bool	wall_in_the_way_hori(t_map *map, int new_cx, int new_cy)
{
	t_data	*data;
	char	**img;
	int		radius;
	int		boundx;

	data = map->data;
	img = map->img_array;
	radius = data->pl_dia / 2;

	boundx = data->mmp_w;
	
	if (((new_cx + radius) < boundx) && img[new_cy][new_cx + radius] == '1')	// right
		return (true);
	if (((new_cx - radius) >= 0) && img[new_cy][new_cx - radius] == '1')		//left
		return (true);
	return (false);
}

bool	wall_in_the_way_vert(t_map *map, int new_cx, int new_cy)
{
	t_data	*data;
	char	**img;
	int		radius;
	int		boundy;

	data = map->data;
	img = map->img_array;
	radius = data->pl_dia / 2;

	boundy = data->mmp_h;
	
	if (((new_cy + radius) < boundy) && img[new_cy + radius][new_cx] == '1')	// up
		return (true);
	if (((new_cy - radius) >= 0) && img[new_cy - radius][new_cx] == '1')		//down
		return (true);
	return (false);
}

// bool	wall_in_the_way(t_game *game, int new_x, int new_y)
// {
// 	int		radius;
// 	int		i;
// 	int		j;

// 	radius = game->data->pl_dia / 2;
// 	i = -radius;
// 	// Check for wall collisions in the new position
// 	while (i < radius)
// 	{
// 		j = -radius;
// 		while  (j <= radius)
// 		{
// 			if (is_wall(game->map->img_array[new_y + j][new_x + i]))
// 				return (true);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (false);
// }

// static bool	is_wall(char c)
// {
// 	if (c == '1')
// 		return (true);
// 	return (false);
// }
