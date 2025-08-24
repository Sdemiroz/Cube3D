/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:33:10 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/24 13:09:41 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cast_rays(t_map *map, t_rays **rays, t_data *data);

static void	calculate_ray_length(t_rays *ray, char **img, t_data *data);
static void	initialize_xvars(t_rays *ray, t_data *data, double *hype_x, double *hop_x);
static void	initialize_yvars(t_rays *ray, t_data *data, double *hype_y, double *hop_y);
static void	update_distance(double *distance, t_dvec *hype, t_dvec hype_step);
static void extract_xy(t_rays *ray, t_ivec *hit, double distance, t_dvec hop);
static bool	check_hit(t_data *data, char **img, t_ivec hit, t_dvec hop);

void	cast_rays(t_map *map, t_rays **rays, t_data *data)
{
	char	**img;
	int		total_rays;
	int		i;

	// if (data->fov_toggle == false)
	// 	return ;
	img = map->img_array;
	total_rays = data->num_rays;
	i = -1;
	while (++i < total_rays)
		calculate_ray_length(rays[i], img, data);
}

// static void	calculate_ray_length(t_rays *ray, t_map *map, t_data *data)
static void	calculate_ray_length(t_rays *ray, char **img, t_data *data)
{
	t_dvec	hype;													// ray-length along hypotenuse corresponding to ray-length along x and y
	t_dvec	hop;
	t_ivec	hit;
	t_dvec	hype_step;
	double	distance[2];

	initialize_xvars(ray, data, &(hype.x), &(hop.x));
	initialize_yvars(ray, data, &(hype.y), &(hop.y));
	hype_step.x = fabs((double)data->tile_size * ray->coeff.x);
	hype_step.y = fabs((double)data->tile_size * ray->coeff.y);
	distance[0] = 0;
	distance[1] = ft_maxi(data->mmp_w, data->mmp_h);
	while (distance[0] <= distance[1])
	{
		update_distance(distance, &hype, hype_step);
		extract_xy(ray, &hit, *distance, hop);
		if (check_hit(data, img, hit, hop))
		{
			ray->length = (int)(distance[0]);
			ray->hit_x = hit.x;
			ray->hit_y = hit.y;
			break ;
		}
	}
}

static void	initialize_xvars(t_rays *ray, t_data *data, double *hype_x, double *hop_x)
{
	double	start_x;
	double	next_x;
	double	tile_size;

	start_x = (double)(data->pl_center_x);
	tile_size = (double)data->tile_size;
	if (ray->cosine > 1e-6)											// facing right
	{
		next_x = ((int)(start_x / tile_size) + 1) * tile_size;		// truncate start_x position to the next hor. tile
		*hype_x = fabs((next_x - start_x) * ray->coeff.x);			// h = b/cos()
		*hop_x = tile_size;
	}
	else if (fabs(ray->cosine) < 1e-6)								// facing vertically up or down
	{
		next_x = start_x;
		*hype_x = ft_maxi(data->mmp_w, data->mmp_h);				// setting to an arbitrary max value if cosine is zero
		*hop_x = 0;
	}
	else															// facing left
	{
		next_x = ((int)(start_x / tile_size)) * tile_size;			// truncate start_x position to the previous hor. tile
		*hype_x = fabs((start_x - next_x) * ray->coeff.x);			// h = b/cos()
		*hop_x = -tile_size;
	}
}

static void	initialize_yvars(t_rays *ray, t_data *data, double *hype_y, double *hop_y)
{
	double	start_y;
	double	next_y;
	double	tile_size;

	start_y = (double)(data->pl_center_y);
	tile_size = (double)data->tile_size;
	if (ray->sine > 1e-6)											// facing up
	{
		next_y = ((int)(start_y / tile_size)) * tile_size;			// truncate starty position to the previous vert. tile
		*hype_y = fabs((start_y - next_y) * ray->coeff.y);			// h = p/sin()
		*hop_y = -tile_size;
	}
	else if (fabs(ray->sine) < 1e-6)								// facing horizontally left or right
	{
		next_y = start_y;
		*hype_y = ft_maxi(data->mmp_w, data->mmp_h);				// setting to an arbitrary max value if sine is zero
		*hop_y = 0;
	}
	else															// facing down
	{
		next_y = ((int)(start_y / tile_size) + 1) * tile_size;		// truncate starty position to the next vert. tile
		*hype_y = fabs((next_y - start_y) * ray->coeff.y);			// h = p/sin()
		*hop_y = tile_size;
	} 
}

static void	update_distance(double *distance, t_dvec *hype, t_dvec hype_step)
{
	if (hype->x < hype->y)
	{
		*distance = hype->x;
		hype->x += hype_step.x;
	}
	else
	{
		*distance = hype->y ;
		hype->y += hype_step.y;
	}
}

static void extract_xy(t_rays *ray, t_ivec *hit, double distance, t_dvec hop)
{
	hit->x = ((*ray->center_x) + distance * ray->cosine);
	hit->y = ((*ray->center_y) - distance * ray->sine);
	if (hop.x < 0)
		hit->x--;
	else
		hit->x++;
	if (hop.y < 0)
		hit->y--;
	else
		hit->y++;
}

static bool	check_hit(t_data *data, char **img, t_ivec hit, t_dvec hop)
{
	if (hit.x >= 0 && hit.x < data->mmp_w && hit.y >= 0 && hit.y < data->mmp_h)
	{
		if (img[hit.y][hit.x] == '1')
			return (true);
		else if (hop.x > 0 && hop.y > 0 &&
				(img[hit.y][hit.x - 1] == '1' || img[hit.y - 1][hit.x] == '1'))
			return (true);
		else if (hop.x > 0 && hop.y < 0 &&
				(img[hit.y][hit.x - 1] == '1' || img[hit.y + 1][hit.x] == '1'))
			return (true);
		else if (hop.x < 0 && hop.y < 0 &&
				(img[hit.y][hit.x + 1] == '1' || img[hit.y + 1][hit.x] == '1'))
			return (true);
		else if (hop.x < 0 && hop.y > 0 &&
				(img[hit.y][hit.x + 1] == '1' || img[hit.y - 1][hit.x] == '1'))
			return (true);
	}
	return (false);
}
