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

static bool	is_wall_pixel(char **img, int width, int height, double x, double y)
{
	int	base_x;
	int	base_y;
	int	dx;
	int	dy;

	base_x = (int)floor(x);
	base_y = (int)floor(y);
	dy = -1;
	while (++dy <= 1)
	{
		int	py;

		py = base_y + dy;
		if (py < 0 || py >= height)
			return (true);
		dx = -1;
		while (++dx <= 1)
		{
			int	px;

			px = base_x + dx;
			if (px < 0 || px >= width)
				return (true);
			if (img[py][px] == '1')
				return (true);
		}
	}
	return (false);
}

bool	wall_collision_circle(t_map *map, double center_x, double center_y)
{
	t_data	*data;
	char	**img;
	int		radius;
	int		width;
	int		height;
	int		i;
	const double	offsets[][2] = {
		{0.0, 0.0},
		{1.0, 0.0}, {-1.0, 0.0}, {0.0, 1.0}, {0.0, -1.0},
		{1.0, 1.0}, {1.0, -1.0}, {-1.0, 1.0}, {-1.0, -1.0},
		{1.0, 0.5}, {1.0, -0.5}, {-1.0, 0.5}, {-1.0, -0.5},
		{0.5, 1.0}, {-0.5, 1.0}, {0.5, -1.0}, {-0.5, -1.0}
	};
	int		check_count;

	data = map->data;
	img = map->img_array;
	radius = data->pl_dia / 2;
	width = data->mmp_w;
	height = data->mmp_h;
	if (center_x - radius < 0 || center_y - radius < 0
		|| center_x + radius >= width || center_y + radius >= height)
		return (true);
	check_count = sizeof(offsets) / sizeof(offsets[0]);
	i = -1;
	while (++i < check_count)
	{
		double	sample_x;
		double	sample_y;

		sample_x = center_x + offsets[i][0] * radius;
		sample_y = center_y + offsets[i][1] * radius;
		if (is_wall_pixel(img, width, height, sample_x, sample_y))
			return (true);
	}

	return (false);
}
