/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:48:37 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/07 14:19:43 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
Function to check if there is a wall in the way of the player's movement
  - The next coordinates of the player circle is checked with respect to its
    center and diameter, against the img_array
  - The player blob is treated as a rectangle to check for colliding coordinates
  - The function returns true if the resulting coordinates after the applied
	movement overlap with the wall coordinates in the map i.e. values 1

*/
bool	wall_in_the_way(t_game *game, int new_x, int new_y)
{
	
}
