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
#include <stddef.h>

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

static const double	g_circle_offsets[][2] = {
	{0.0, 0.0},
	{1.0, 0.0}, {-1.0, 0.0}, {0.0, 1.0}, {0.0, -1.0},
	{1.0, 1.0}, {1.0, -1.0}, {-1.0, 1.0}, {-1.0, -1.0},
	{1.0, 0.5}, {1.0, -0.5}, {-1.0, 0.5}, {-1.0, -0.5},
	{0.5, 1.0}, {-0.5, 1.0}, {0.5, -1.0}, {-0.5, -1.0}
};
static const size_t	g_circle_offset_count = sizeof(g_circle_offsets) / sizeof(g_circle_offsets[0]);

bool	wall_collision_circle(t_map *map, double center_x, double center_y)
{
	t_data	*data;
	char	**img;
	double	radius;
	int		width;
	int		height;
	size_t	idx;

	if (!map || !map->data || !map->img_array)
		return (true);
	data = map->data;
	img = map->img_array;
	radius = (double)data->pl_dia * 0.5;
	if (radius <= 0.0)
		return (false);
	width = data->mmp_w;
	height = data->mmp_h;
	if (center_x - radius < 0.0 || center_y - radius < 0.0
		|| center_x + radius >= (double)width || center_y + radius >= (double)height)
		return (true);
	idx = 0;
	while (idx < g_circle_offset_count)
	{
		double	sample_x;
		double	sample_y;
		int		px;
		int		py;

		sample_x = center_x + g_circle_offsets[idx][0] * radius;
		sample_y = center_y + g_circle_offsets[idx][1] * radius;
		px = (int)floor(sample_x);
		py = (int)floor(sample_y);
		if (px < 0 || px >= width || py < 0 || py >= height)
			return (true);
		if (img[py][px] == '1')
			return (true);
		idx++;
	}

	return (false);
}
