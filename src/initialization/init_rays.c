/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:07:21 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/31 13:05:39 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_rays(t_rays **rays);

static void	init_ray_delta(t_rays *ray, int num_rays, int i, t_data *data);
static void	init_ray_angle(t_rays *ray);
static void	init_ray_trig_coeffs(t_rays *ray, t_data *data);

void	init_rays(t_rays **rays)
{
	t_data		*data;
	int			i;
	int			num_rays;
	t_rays		*ray;
	
	data = get_data();
	num_rays = data->num_rays;
	i = -1;
	while (++i < num_rays)
	{
		ray = rays[i];
		ray->index = i;
		init_ray_delta(ray, num_rays, i, data);									// Left rays -> -ve delta, Right rays -> +ve delta
		ray->prev_dir = &data->prev_dir;
		ray->cur_dir = &data->cur_dir;
		init_ray_angle(ray);													// Angles calculated as per normal convention used the in the program elsewhere
		init_ray_trig_coeffs(ray, data);
		ray->length = ft_maxi(data->mmp_w, data->mmp_h) - 2 * data->tile_size;	// Preliminary initialising value
		ray->center_x = &data->pl_center_x;
		ray->center_y = &data->pl_center_y;
		ray->center_x_d = &data->pl_center_x_d;
		ray->center_y_d = &data->pl_center_y_d;
		ray->hit_x = -1;
		ray->hit_y = -1;
		ray->inv_wall_distance = 0.0;
		ray->tex_u = 0.0;
	}
}

// // Rays are distributed with an equal 1 degree delta across the FOV
// static void	init_ray_delta(t_rays *ray, int num_rays, int i, t_data *data)
// {
// 	if (num_rays % 2 == 0)
// 	{
// 		if (i < num_rays / 2)
// 			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
// 		else
// 			ray->delta = ((double)(i + 1 - (num_rays / 2))) * PI / 180;
// 	}
// 	else
// 	{
// 		if (i < num_rays / 2)
// 			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
// 		else if (i == num_rays / 2)
// 			ray->delta = 0;
// 		else if (i > num_rays / 2)
// 			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
// 	}	
// }

// Rays are distributed equidistantly across the FOV
static void	init_ray_delta(t_rays *ray, int num_rays, int i, t_data *data)
{
	double	equi_delta;
	double	fov;
	int		fov2;

	fov = data->fov;
	fov2 = (int)fov / 2;
	equi_delta = fov / (double)(num_rays - 1);
	ray->delta = ((i * equi_delta - (double)fov2)) * PI / 180;
}

static void	init_ray_angle(t_rays *ray)
{
	double	ray_delta;
	double	cur_dir;
	double	pi2;
	
	ray_delta = ray->delta;
	cur_dir = *ray->cur_dir;
	pi2 = 2 * PI;
	ray->angle = cur_dir - ray_delta;

	if (ray->angle < 0)
		ray->angle += pi2; // Normalize to [0, 2*PI]
	else if (ray->angle >= pi2)
		ray->angle -= pi2; // Normalize to [0, 2*PI]
}

static void	init_ray_trig_coeffs(t_rays *ray, t_data *data)
{
	ray->cosine = cos(ray->angle);
	ray->sine = sin(ray->angle);
	if (fabs(ray->cosine) > 1e-6)												// if the cosine ratio is non-zero
		ray->coeff.x = 1 / ray->cosine;
	else
		ray->coeff.x = data->mmp_w;												// setting to an arbitrary max value if cosine is zero
	if (fabs(ray->sine) > 1e-6)													// if the sine ratio is non-zero
		ray->coeff.y = 1 / ray->sine;
	else
		ray->coeff.y = data->mmp_h;												// setting to an arbitrary max value if sine is zero
}
