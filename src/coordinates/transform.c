/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 22:04:52 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/05 19:43:28 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	to_map_xy(int *map_xy, int img_x, int img_y);
void	to_img_xy(int *img_xy, int map_x, int map_y);

void	to_map_xy(int *map_xy, int img_x, int img_y)
{
	// t_data	*data;
	int	tile_size;
	
	tile_size = get_data()->tile_size;
	map_xy[0] = img_x / tile_size;
	map_xy[1] = img_y / tile_size;
}

void	to_img_xy(int *img_xy, int map_x, int map_y)
{
	int	tile_size;
	
	tile_size = get_data()->tile_size;
	img_xy[0] = map_x * tile_size + tile_size / 2;
	img_xy[1] = map_y * tile_size + tile_size / 2;
}
