/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:29:06 by pamatya           #+#    #+#             */
/*   Updated: 2025/09/11 21:35:44 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void initialize_ray_caster(t_rays *ray, t_data *data, t_dvec *d_ptr[],
		t_ivec *check);

static void	initialize_xvars(t_rays *ray, t_data *data, double *hype_x,
		double *hop_x);
static void	initialize_yvars(t_rays *ray, t_data *data, double *hype_y,
		double *hop_y);


// !! Struct check could simply be used as an int variable with toggle between 1 and 0
void initialize_ray_caster(t_rays *ray, t_data *data, t_dvec *d_ptr[],
		t_ivec *check)
{
	t_dvec	*hop;
	t_dvec	*hype;

	hop = *d_ptr;
	hype = *(d_ptr + 1);
	initialize_xvars(ray, data, &(hype[0].x), &(hop->x));
	initialize_yvars(ray, data, &(hype[0].y), &(hop->y));
	if (hype[0].x < hype[0].y)
	{
		check->x = 1;
		check->y = 0;
	}
	else
	{
		check->x = 0;
		check->y = 1;	
	}
	hype[1].x = fabs((double)data->tile_size * ray->coeff.x);	// hope[1] is the unit step length along hypotenuse, per unit step along x and y
	hype[1].y = fabs((double)data->tile_size * ray->coeff.y);
	hype[2].x = 0;												// hype[2].x prev. distance[0]
	hype[2].y = 2 * ft_maxi(data->mmp_w, data->mmp_h);			// hype[2].y prev. distance[1]
}

static void	initialize_xvars(t_rays *ray, t_data *data, double *hype_x,
		double *hop_x)
{
	double	start_x;
	double	next_x;
	double	tile_size;

	start_x = data->pl_center_x_d;
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

static void	initialize_yvars(t_rays *ray, t_data *data, double *hype_y,
		double *hop_y)
{
	double	start_y;
	double	next_y;
	double	tile_size;

	start_y = data->pl_center_y_d;
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

// static void	initialize_axis_check(t_dvec *hype, t_ivec *check)
// {
// 	if (hype[0].x < hype[0].y)
// 	{
// 		check->x = 1;
// 		check->y = 0;
// 	}
// 	else
// 	{
// 		check->x = 0;
// 		check->y = 1;	
// 	}
// }
