/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:33:10 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/21 00:49:34 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cast_rays(t_map *map, t_rays **rays, t_data *data);

static void	calculate_ray_length(t_map *map, t_rays *ray, t_data *data);
static int inline	ft_maxi(int x, int y);
// static double inline	ft_maxd(double x, double y);


void	cast_rays(t_map *map, t_rays **rays, t_data *data)
{
	t_rays	*ray;
	int		i;
	int		total_rays;

	if (data->fov_toggle == false)
		return ;
	total_rays = data->num_rays;
	i = -1;
	// printf("About to cast some rays\n");
	while (++i < total_rays)
	{
		ray = rays[i];
		// printf("\033[0;31mRay[%d]; pl_pos: x = %d, y = %d; ray_start: x = %d and y = %d\033[0m\n", ray->index, data->pl_posx, data->pl_posy, *ray->center_x, *ray->center_y);
		calculate_ray_length(map, ray, data);
		// printf("\n\n\n");
		// printf("Probably casted this ray\n");
	}
	// test_print_rays('d');
	// printf("RAY CASTED\n");
}

static void	calculate_ray_length(t_map *map, t_rays *ray, t_data *data)
{
	t_dvec	hype;			// ray-length along hypotenuse corresponding to ray-length along x and y
	t_dvec	start;
	t_dvec	next_stop;
	t_dvec	hype_unit_step;
	t_dvec	hop;
	t_dvec	coeff;
	double	tile_size;
	t_ivec	map_size;
	int		x;
	int		y;
	char	**img_array;
	bool	tile_found;
	double	max_distance;
	double	distance;
	
	tile_size = (double)data->tile_size;
	img_array = map->img_array;
	
	tile_found = false;

	map_size.x = data->mmp_w;
	map_size.y = data->mmp_h;
	max_distance = ft_maxi(map_size.x, map_size.y);

	start.x = (double)(*ray->center_x);
	start.y = (double)(*ray->center_y);

	if (fabs(ray->cosine) > 1e-6)													// if the cosine ratio is non-zero
		coeff.x = 1 / ray->cosine;
	else
		coeff.x = map_size.x;														// setting to an arbitrary max value if cosine is zero
	
	if (fabs(ray->sine) > 1e-6)														// if the sine ratio is non-zero
		coeff.y = 1 / ray->sine;
	else
		coeff.y = map_size.y;														// setting to an arbitrary max value if sine is zero

	hype.x = 0;
	hype.y = 0;
	
	// printf("ray: startx = %.2f,  starty = %.2f,  cur_dirn = %.2f,  delta = %.2f,  ray->angle = %.2f degrees\n", start.x, start.y, (data->cur_dir * 180 / PI), (ray->delta * 180 / PI), (ray->angle * 180 / PI));
	
// ------------- Initializing first values before the loop ------------- //
	// In x-axis ---------------------------------------------------------
	if (ray->cosine > 1e-6)				// facing right
	{
		next_stop.x = (double)((int)(start.x / tile_size) + 1) * tile_size;				// truncate startx position to the next hor. tile
		hype.x = fabs((next_stop.x - start.x) * coeff.x);							// h = b/cos()
		hop.x = tile_size;
	}
	else if (fabs(ray->cosine) < 1e-6)	// facing vertically up or down
	{
		next_stop.x = start.x;
		hype.x = max_distance;			// setting to an arbitrary max value if cosine is zero
		hop.x = 0;
		// printf("hype.x set to max_distance = %.2f\n", max_distance);
	}
	else								// facing left
	{
		next_stop.x = (double)(int)(start.x / tile_size) * tile_size;					// truncate startx position to the previous hor. tile
		hype.x = fabs((start.x - next_stop.x) * coeff.x);							// h = b/cos()
		hop.x = -tile_size;
	}
	// In x-axis =========================================================

	// In y-axis ---------------------------------------------------------
	if (ray->sine > 1e-6)					// facing up
	{
		next_stop.y = (double)(int)(start.y / tile_size) * tile_size;					// truncate starty position to the previous vert. tile
		hype.y = fabs((start.y - next_stop.y) * coeff.y);							// h = p/sin()
		hop.y = -tile_size;
	}
	else if (fabs(ray->sine) < 1e-6)	// facing horizontally left or right
	{
		next_stop.y = start.y;
		hype.y = max_distance;			// setting to an arbitrary max value if sine is zero
		hop.y = 0;
		// printf("hype.y set to max_distance = %.2f\n", max_distance);
	}
	else								// facing down
	{
		next_stop.y = (double)((int)(start.y / tile_size) + 1) * tile_size;				// truncate starty position to the next vert. tile
		hype.y = fabs((next_stop.y - start.y) * coeff.y);							// h = p/sin()
		hop.y = tile_size;
	}
	// In y-axis =========================================================
	
	// printf("\n");
	// printf("current.x = %.2f,  current.y = %.2f,  hp.x = %.2f,  hp.y = %.2f,  distance = %.2f\n", next_stop.x, next_stop.y, hype.x, hype.y, distance);
	// printf("\n");
	
// ====================================================================== //

// ----------- Start of loop to find the tile hit by the ray ----------- //
	hype_unit_step.x = fabs(tile_size * coeff.x);
	hype_unit_step.y = fabs(tile_size * coeff.y);
	// printf("hop.x = %.2f,  hop.y = %.2f\n", hop.x, hop.y);
	// printf("hype_unit_step.x = %.2f,  \thype_unit_step.y = %.2f\n\n\n", hype_unit_step.x, hype_unit_step.y);
	distance = 0;
	while (!tile_found && distance <= max_distance)
	{
		// 1st method of stepping: works well with 5th method of extraction
		if (hype.x < hype.y)
		{
			next_stop.x += hop.x;
			distance = hype.x;
			hype.x += hype_unit_step.x;
		}
		else
		{
			next_stop.y += hop.y;
			distance = hype.y ;
			hype.y += hype_unit_step.y;
		}
		
		// // 2nd method of stepping: to try with 4th method of extraction; doesn't
		// // work with either of the methods of extraction (4th and 5th)
		// if (hype.x < hype.y)
		// {
		// 	next_stop.x += hop.x;
		// 	distance = hype.x + ray->cosine;	// Adding 1 x-axis unit equivalent of hypotenuse to the distance in the form of cosine (dh = pcosA, p = 1)
		// 	hype.x += hype_unit_step.x;
		// }
		// else
		// {
		// 	next_stop.y += hop.y;
		// 	distance = hype.y + ray->sine;		// Adding 1 y-axis unit equivalent of hypotenuse to the distance in the form of sine (dh = bsinA, b = 1)
		// 	hype.y += hype_unit_step.y;
		// }
		
		// -------- Extracting x and y -----------------------------------------
		// // 4th method: does not work with either the 1st or the 2nd methods of stepping
		// x = (int)(start.x + distance * ray->cosine);
		// y = (int)(start.y - distance * ray->sine);		

		// 5th method: works well except for some rays seeping through open corners
		x = (int)(start.x + distance * ray->cosine);
		y = (int)(start.y - distance * ray->sine);
		if (hop.x < 0)
			x--;
		else
			x++;
		if (hop.y < 0)
			y--;
		else
			y++;
		
		// // 6th method: trying to increment the hit coordinate in the direction
		// // of the ray, then casting to int and saving it; doesn't work
		// double ix = (start.x + distance * ray->cosine);
		// double iy = (start.y - distance * ray->sine);
		// if (hop.x < 0)
		// 	x = (int)(ix - ray->cosine);
		// else
		// 	x = (int)(ix + ray->cosine);
		// if (hop.y < 0)
		// 	y = (int)(iy - ray->sine);
		// else
		// 	y = (int)(iy + ray->sine);

		// // 7th method: trying to increaes the distance by 1 in the direction 
		// // of the ray one axis at a time, and extracting x or y; doesn't work
		// double	dist = distance;
		// if (hop.x < 0)
		// 	distance--;
		// else
		// 	distance++;
		// x = (int)(start.x + distance * ray->cosine);
		// distance = dist;	// Resetting distance to the previous value
		// if (hop.y < 0)
		// distance--;
		// else
		// distance++;
		// y = (int)(start.y - distance * ray->sine);
		// distance = dist;

		// ======== Extracting x and y =========================================

		// printf("current.x = %.2f,  current.y = %.2f  \n", next_stop.x, next_stop.y);
		// printf("hype.x = %.2f,  hype.y = %.2f,  distance = %.2f,  \tx = %d, y = %d\n\n", hype.x, hype.y, distance, x, y);	
		
		if (x >= 0 && x < map_size.x && y >= 0 && y < map_size.y)
		{
			// // 1st method: worked well with the 5th method of extraction but
			// // still had few seeping rays, although fewer than without the
			// // extra else-if conditions
			// if (img_array[y][x] == '1')
			// 	tile_found = true;
			// else if (hop.x > 0 && hop.y > 0 && img_array[y][x - 1] == '1' && img_array[y - 1][x] == '1')
			// 	tile_found = true;
			// else if (hop.x > 0 && hop.y < 0 && img_array[y][x - 1] == '1' && img_array[y + 1][x] == '1')
			// 	tile_found = true;
			// else if (hop.x < 0 && hop.y < 0 && img_array[y][x + 1] == '1' && img_array[y + 1][x] == '1')
			// 	tile_found = true;
			// else if (hop.x < 0 && hop.y > 0 && img_array[y][x + 1] == '1' && img_array[y - 1][x] == '1')
			// 	tile_found = true;

			// 2nd method: works well with the 5th method of extraction, no more
			// seeping rays
			if (img_array[y][x] == '1')
				tile_found = true;
			else if (hop.x > 0 && hop.y > 0 && (img_array[y][x - 1] == '1' || img_array[y - 1][x] == '1'))
				tile_found = true;
			else if (hop.x > 0 && hop.y < 0 && (img_array[y][x - 1] == '1' || img_array[y + 1][x] == '1'))
				tile_found = true;
			else if (hop.x < 0 && hop.y < 0 && (img_array[y][x + 1] == '1' || img_array[y + 1][x] == '1'))
				tile_found = true;
			else if (hop.x < 0 && hop.y > 0 && (img_array[y][x + 1] == '1' || img_array[y - 1][x] == '1'))
				tile_found = true;
		}
	}
// ===================================================================== //
	
// ------ After the loop, we have the ray length and hit position ------ //
	if (tile_found)
	{
		ray->length = (int)distance;
		ray->hit_x = x;
		ray->hit_y = y;
	}
	else
	{
		ray->length = ft_maxi(map_size.x, map_size.y);
		ray->hit_x = -1;
		ray->hit_y = -1;
	}

	double	dx = ray->hit_x - *ray->center_x;
	double	dy = ray->hit_y - *ray->center_y;
	double	len = sqrt((dx * dx) + (dy * dy));
	// printf("ray_len = %.2f,  hitx = %d,  hity = %d,  coord_len = %.2f,  del = %.2f\n", ray->length, ray->hit_x, ray->hit_y, len, (len - ray->length));	
// ===================================================================== //
}

static int inline	ft_maxi(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}

// static double inline	ft_maxd(double x, double y)
// {
// 	if (x >= y)
// 		return x;
// 	else
// 		return y;
// }
