/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:48:37 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/05 20:38:24 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function to check if there is a wall in the way of the player's movement
bool	wall_in_the_way(t_game *game, int new_x, int new_y)
{
	t_map	*map;
	char	**map_array;
	int		map_x;
	int		map_y;
	
	map = game->map;
	map_array = map->map_array;
	to_map_xy((int[2]){map_x, map_y}, new_x, new_y);
	if (map_x < 0 || map_y < 0 || map_x >= map->data->tiles_x || map_y >= map->data->tiles_y)
		return (true); // Out of bounds
	if (map_array[map_y][map_x] == '1')
		return (true); // Wall found
	return (false); // No wall in the way
}
