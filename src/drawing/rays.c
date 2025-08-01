/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:51:11 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/01 20:31:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	draw_player_direction(t_map *map);
void	draw_player_direction(t_player *pl, t_data *data);
void	erase_prev_direction(t_player *pl, t_data *data);
void	draw_cur_direction(t_player *pl, t_data *data);

void	erase_ray(t_player * pl, t_rays *ray);
void	update_ray_attr(t_rays *ray);
void	draw_ray(t_player * pl, t_rays *ray);

/*
Function to draw the player direction as a line extending from the center of
the player blob, but by only updating the instance with the line orientation and
not redrawing the whole blob image.
  - distance = x * sqrt(1 + tan * tan)
*/
void	draw_player_direction(t_player *pl, t_data *data)
{
	t_img	*view;

	view = pl->view;
	if (data->prev_dir != data->cur_dir)
		erase_prev_direction(pl, data);
	// data->prev_dir = data->cur_dir;
	draw_cur_direction(pl, data);
}

void	erase_prev_direction(t_player *pl, t_data *data)
{
	int		center_x;
	int		center_y;
	double	distance;
	int		ix;
	int		iy;

	center_x = data->pl_center_x;
	center_y = data->pl_center_y;
	distance = 0;
	while (distance++ < 8)
	{
		ix = center_x + (int)(distance * data->cosine);	// As for image coordinates, right is still plus positive and left is still negative
		iy = center_y - (int)(distance * data->sine); // As for image coordinates, up is negative/decrement and down is positive/increment
		mlx_put_pixel(pl->view, ix, iy, RESET);
	}
}

void	draw_cur_direction(t_player *pl, t_data *data)
{
	int		center_x;
	int		center_y;
	double	distance;
	int		ix;
	int		iy;

	data->sine = sin(data->cur_dir);
	data->cosine = cos(data->cur_dir);
	center_x = data->pl_center_x;
	center_y = data->pl_center_y;
	distance = 0;
	while (distance++ < 8)
	{
		ix = center_x + (int)(distance * data->cosine);	// As for image coordinates, right is still plus positive and left is still negative
		iy = center_y - (int)(distance * data->sine); // As for image coordinates, up is negative/decrement and down is positive/increment
		mlx_put_pixel(pl->view, ix, iy, RED);
	}
}

/*
Function to erase and redraw the whole fov
	- for a streamlined erasure and redrawing of all fov rays in a single loop
	- called from turn_player
*/
void	redraw_fov(t_player *pl, t_rays **rays)
{
	t_data	*data;
	t_rays	*ray;
	int		num_rays;
	double	dir[2];
	int		i;
	bool	direction_changed;

	data = get_data();
	num_rays = data->num_rays;
	dir[0] = data->prev_dir;	// Assigning the previous direction to dir[0]
	dir[1] = data->cur_dir; 	// Assigning the current direction to dir[1]
	
	direction_changed = (fabs(dir[0] - dir[1]) > 1e-9);
	
	i = -1;
	while (++i < num_rays)
	{
		ray = rays[i];
		// if (dir[0] != dir[1])
		if (direction_changed)
		{
			erase_ray(pl, ray);
			update_ray_attr(ray);
		}
		draw_ray(pl, ray);
	}
}


void	erase_ray(t_player * pl, t_rays *ray)
{
	int	i;
	int	ix;
	int	iy;

	i = -1;
	while (++i < ray->length)
	{
		ix = *ray->start_x + (int)(i * ray->cosine);
		iy = *ray->start_y - (int)(i * ray->sine);
		mlx_put_pixel(pl->view, ix, iy, RESET);
	}
}

void	update_ray_attr(t_rays *ray)
{
	double	pi2;

	pi2 = 2 * PI;
	ray->angle = *ray->cur_dir - ray->delta;
	if (ray->angle < 0)
		ray->angle += 2 * PI; // Normalize to [0, 2*PI]
	else if (ray->angle >= 2 * PI)
		ray->angle -= 2 * PI; // Normalize to [0, 2*PI]
	ray->cosine = cos(ray->angle);
	ray->sine = sin(ray->angle);
}

void	draw_ray(t_player * pl, t_rays *ray)
{
	int	i;
	int	ix;
	int	iy;

	i = -1;
	while (++i < ray->length)
	{
		ix = *ray->start_x + (int)(i * ray->cosine);
		iy = *ray->start_y - (int)(i * ray->sine);
		mlx_put_pixel(pl->view, ix, iy, DEBUG_GREEN2);
	}
}

/*
Function to erase the whole fov rays previously drawn
	- Utilizes erase_ray in a loop to achieve this
*/
void	erase_previous_fov(t_player *pl, t_rays **rays)
{
	int		num_rays;
	int		i;
	
	if (pl->data->fov_toggle == false)
		return ;
	num_rays = pl->data->num_rays;
	i = -1;
	while (++i < num_rays)
		erase_ray(pl, rays[i]);
}

/*
Function to draw the whole fov rays
	- Utilizes draw_ray in a loop to achieve this
*/
void	draw_current_fov(t_player *pl, t_rays **rays)
{
	int		num_rays;
	int		i;
	
	if (pl->data->fov_toggle == false)
		return ;
	num_rays = pl->data->num_rays;
	i = -1;
	while (++i < num_rays)
		draw_ray(pl, rays[i]);
}

void	update_ray_attr_all(t_rays **rays)
{
	t_rays	*ray;
	double	pi2;
	int		i;
	int		num_rays;
	double	factor;
	
	num_rays = get_data()->num_rays;
	pi2 = 2 * PI;
	factor = (180 / PI);
	i = -1;
	// while (++i < num_rays)
	// {
	// 	ray = rays[i];
	// 	ray->angle = *ray->cur_dir - ray->delta;
	// 	if (ray->angle < 0)
	// 		ray->angle += pi2; // Normalize to [0, 2*PI]
	// 	else if (ray->angle >= pi2)
	// 		ray->angle -= pi2; // Normalize to [0, 2*PI]
	// 	ray->cosine = cos(ray->angle);
	// 	ray->sine = sin(ray->angle);
	// }
	while (++i < num_rays)
	{
		ray = rays[i];
		update_ray_attr(ray);
	}
}
