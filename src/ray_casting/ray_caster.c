/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:33:10 by pamatya           #+#    #+#             */
/*   Updated: 2025/09/14 14:12:15 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cast_rays(t_map *map, t_rays **rays, t_data *data);

static void	calculate_ray_length(t_game *game, t_rays *ray, char **img,
		t_data *data);
static void	update_distance(t_dvec *hype, t_ivec *check);
static void extract_xy(t_rays *ray, double distance, t_ivec *ptr[], t_dvec hop);
static void	assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop,
		t_ivec check);

void	cast_rays(t_map *map, t_rays **rays, t_data *data)
{
	t_game	*game;
	char	**img;
	int		total_rays;
	int		i;

	// if (data->fov_toggle == false)
	// 	return ;
	game = map->game;
	img = map->img_array;
	total_rays = data->num_rays;
	i = -1;
	while (++i < total_rays)
		calculate_ray_length(game, rays[i], img, data);
}

// // !! ray-length re-calculation with new hit.x,y might be a better estimation of the wall distance
// static void	calculate_ray_length(t_game *game, t_rays *ray, char **img,
// 		t_data *data)
// {
// 	t_ivec	hit;
// 	t_ivec	check;
// 	t_dvec	hop;
// 	t_dvec	hype[3];								// hype[0] is ray-length along hypotenuse to length along x and y, and hope[1] is the unit step length along hypotenuse per unit step along x and y, hype[2] is to replace double distance[2] with hype[2].x as distance[0] and hype[2].y as distance[1]

// 	initialize_ray_caster(ray, data, (t_ivec *[]){&hit, &check},
// 			(t_dvec *[]){&hop, hype});
// 	while (hype[2].x <= hype[2].y)
// 	{
// 		update_distance(hype, &check);
// 		extract_xy(ray, hype[2].x, (t_ivec *[]){&hit, &check}, hop);
// 		if (check_hit(data, img, hit, hop))
// 		{
// 			ray->length = (int)(hype[2].x);

//			// !! this method of ray-length recalculation with new hit.x,y might be a better estimation of the wall distance
// 			// double start_x = data->pl_center_x;
// 			// double start_y = data->pl_center_y;
// 			// double dx = hit.x - start_x;
// 			// double dy = hit.y - start_y;
// 			// if (check.x)
// 			// 	ray->length = fabs(dx * ray->coeff.x);
// 			// else if (check.y)
// 			// 	ray->length = fabs(dy * ray->coeff.y);
			
// 			ray->hit_x = hit.x;
// 			ray->hit_y = hit.y;
// 			assign_wall_texture(game, ray, hop, check);
// 			break ;
// 		}
// 	}
// 	printf("r%d: %c\t", ray->index, ray->hit_wall);
// }

// !! if the game struct was not needed to be passed to this fn, the start struct
// could be passed instead to save double-dereferencing for each ray per player position
// as the player position is the same for each ray for an instance of the image drawn
// !! another optimization msg in the previous version above (on ray re-calculation)
static void	calculate_ray_length(t_game *game, t_rays *ray, char **img,
		t_data *data)
{
	t_dvec	hop;
	t_dvec	hype[3];								// hype[0] is ray-length along hypotenuse to length along x and y, and hope[1] is the unit step length along hypotenuse per unit step along x and y, hype[2] is to replace double distance[2] with hype[2].x as distance[0] and hype[2].y as distance[1]
	t_ivec	check;
	t_ivec	hit;
	t_ivec	start;

	start.x = (int)(*ray->center_x);
	start.y = (int)(*ray->center_y);
	initialize_ray_caster(ray, data, (t_dvec *[]){&hop, hype}, &check);
	while (hype[2].x <= hype[2].y)
	{
		update_distance(hype, &check);
		extract_xy(ray, hype[2].x, (t_ivec *[]){&hit, &check, &start}, hop);
		if ((hit.x >= 0 && hit.x < data->mmp_w && hit.y >= 0 &&
				hit.y < data->mmp_h) && (img[hit.y][hit.x] == '1'))
		{
				ray->length = (hype[2].x);
				ray->wall_distance = ((hype[2].x) * cos(ray->delta));
				ray->hit_x = hit.x;
				ray->hit_y = hit.y;
				assign_wall_texture(game, ray, hop, check);
				break ;
		}
	}
	// printf("r%d: %c\t", ray->index, ray->hit_wall);
}

static void	update_distance(t_dvec *hype, t_ivec *check)
{
	if (hype[0].x < hype[0].y)		// hype[0] is ray-length along hypotenuse to length along x and y
	{
		hype[2].x = hype[0].x;		// hype[2].x is the distance travelled by the ray
		hype[0].x += hype[1].x;		// hope[1] is the unit step length along hypotenuse per unit step along x and y
		check->x = 1;
		check->y = 0;
	}
	else
	{
		hype[2].x = hype[0].y;		// hype[2].x is the distance travelled by the ray
		hype[0].y += hype[1].y;
		check->x = 0;
		check->y = 1;
	}
}

/*
Function extracts the hit position from distance and then increment it by one
pixel in the direction of the ray. The incrementing is done to avoid the problem
of checking at the boundary of the current tile, and instead checking the first
pixel in the next tile in the direction of the ray
*/
static void extract_xy(t_rays *ray, double distance, t_ivec *ptr[], t_dvec hop)
{
	t_ivec	*hit;
	t_ivec	*check;
	t_ivec	*start;

	hit = *ptr;
	check = *(ptr + 1);
	start = *(ptr + 2);
	// hit->x = ((*ray->center_x) + distance * ray->cosine);
	// hit->y = ((*ray->center_y) - distance * ray->sine);
	hit->x = (start->x + distance * ray->cosine);
	hit->y = (start->y - distance * ray->sine);
	if (check->x)
	{
		if (hop.x < 0)
			hit->x--;
		else
			hit->x++;
	}
	else if (check->y)
	{
		if (hop.y < 0)
			hit->y--;
		else
			hit->y++;
	}
}

static void	assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop, t_ivec check)
{
	if (check.x == 1 && hop.x > 0)
	{
		ray->hit_wall = 'E';	
		ray->tex = game->EA_texture;
	}
	else if (check.x == 1 && hop.x < 0)
	{
		ray->hit_wall = 'W';		
		ray->tex = game->WE_texture;
	}
	else if (check.y == 1 && hop.y < 0)
	{
		ray->hit_wall = 'N';	
		ray->tex = game->NO_texture;
	}
	else if (check.y == 1 && hop.y > 0)
	{
		ray->hit_wall = 'S';
		ray->tex = game->SO_texture;
	}
	else	// might not need this part
		ray->hit_wall = 'X';
}
