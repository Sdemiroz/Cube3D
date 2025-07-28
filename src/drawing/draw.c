/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/28 20:58:15 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		draw_map(t_game *game);

static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int thickness);

// static void	place_block2(t_img *img, int i, int j, int block_color, int bls);
// static void	draw_border2(t_img *img, int	width, int height, int color, int bls);

// void	draw_player_direction(t_map *map);
void	draw_player_direction(t_player *pl, t_data *data);
void	erase_previous_ray(t_player *pl, t_data *data);
void	draw_forward_ray(t_player *pl, t_data *data);

void	draw_map(t_game *game)
{
	t_data	*data;
	char	**map;
	int		i;
	int		j;

	data = game->data;
	map = game->map->map_array;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1')
				place_block(game->map->image, j, i, STONE_GRAY);
			else if (map[i][j] == '0' || is_valid(map[i][j]))
				place_block(game->map->image, i, j, 0);
		}
	}
	draw_player_direction(game->player, data);
	draw_border(game->img3D, data->wind_w, data->wind_h, data->tile_size);
	// draw_border(game->map->image, MAP_W, MAP_H, SAND_YELLOW);
	// draw_border(game->player->blob2D, data->tile_size, data->tile_size, 1);
	place_player2D_2(game, 1);
}

/*
Function to place a block/tile of size as defined in the HEADER as TILE_SIZE
  - if block color is provided as 0, then block_color will be white
  - x and y are the starting coordinates (from upper left corner) of blocks in a
  	tiled world representing the whole block of several pixels TILE_SIZE in 
	width and height
*/
static void	place_block(t_img *img, int x, int y, int block_color)
{
	int		i;
	int		j;
	t_data	*data;

	if (!block_color)
		return ;
	data = get_data();
	j = -1;
	while (++j < data->tile_size)
	{
		if (j == data->tile_size - 1)
			break ;
		else
		{
			i = -1;
			while (++i < data->tile_size)
			{
				if (i == data->tile_size - 1)
					break ;
				mlx_put_pixel(img, x * data->tile_size + i,
						y * data->tile_size + j, block_color);
			}
		}
	}
}

static void	draw_border(t_img *img, int width, int height, int thickness)
{
	int i;
	int	j;
	int	block_x;
	int	block_y;

	i = -1;
	j = -1;
	block_x = width / thickness;
	block_y = height / thickness;
	while (++j < block_y)
	{
		i = -1;
		if (j == 0 || j == (block_y - 1))
			while (++i < block_x)
				place_block(img, i, j, LAVA_RED_DARK);
		else
		{
			while (++i < block_x)
				if (i == 0 || i == (block_x - 1))
					place_block(img, i, j, LAVA_RED_DARK);
		}
	}
}

// bls = TILE_SIZE 
static void	place_block2(t_img *img, int x, int y, int block_color, int bls)
{
	int		i;
	int		j;

	if (!block_color)
		return ;
	j = -1;
	while (++j < bls)
	{
		i = -1;
		while (++i < bls)
			mlx_put_pixel(img, x * bls + i, y * bls + j,
					block_color);
	}
}

// static void	draw_border2(t_img *img, int width, int height, int color, int bls)
// {
// 	int i;
// 	int	j;
// 	int	block_x;
// 	int	block_y;

// 	i = -1;
// 	j = -1;
// 	block_x = width / bls;
// 	block_y = height / bls;
// 	while (++j < block_y)
// 	{
// 		i = -1;
// 		if (j == 0 || j == (block_y - 1))
// 			while (++i < block_x)
// 				place_block2(img, i, j, color, bls);
// 		else
// 		{
// 			while (++i < block_x)
// 				if (i == 0 || i == (block_x - 1))
// 					place_block2(img, i, j, color, bls);	
// 		}
// 	}
// }

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
		erase_previous_ray(pl, data);
	data->prev_dir = data->cur_dir;
	draw_forward_ray(pl, data);
}

void	erase_previous_ray(t_player *pl, t_data *data)
{
	int		center_x;
	int		center_y;
	double	distance;
	int		ix;
	int		iy;

	center_x = data->pl_posx + data->tile_size / 2;
	center_y = data->pl_posy + data->tile_size / 2;
	distance = 0;
	while (distance++ < 8)
	{
		ix = center_x + (int)(distance * data->cosine);	// As for image coordinates, right is still plus positive and left is still negative
		iy = center_y - (int)(distance * data->sine); // As for image coordinates, up is negative/decrement and down is positive/increment
		mlx_put_pixel(pl->view, ix, iy, RESET);
	}
}

void	draw_forward_ray(t_player *pl, t_data *data)
{
	int		center_x;
	int		center_y;
	double	distance;
	int		ix;
	int		iy;

	data->sine = sin(data->cur_dir);
	data->cosine = cos(data->cur_dir);
	center_x = data->pl_posx + data->tile_size / 2;
	center_y = data->pl_posy + data->tile_size / 2;
	distance = 0;
	while (distance++ < 8)
	{
		ix = center_x + (int)(distance * data->cosine);	// As for image coordinates, right is still plus positive and left is still negative
		iy = center_y - (int)(distance * data->sine); // As for image coordinates, up is negative/decrement and down is positive/increment
		mlx_put_pixel(pl->view, ix, iy, RED);
	}
}

// void	draw_ray(t_rays *rays, t_data *data, int ray_index, double dist)
// {
// 	int		center_x;
// 	int		center_y;
// 	double	distance;
// 	int		ix;
// 	int		iy;

// 	data->sine = sin(data->cur_dir);
// 	data->cosine = cos(data->cur_dir);
// 	center_x = data->pl_posx + data->tile_size / 2;
// 	center_y = data->pl_posy + data->tile_size / 2;
// 	distance = 0;
// 	while (distance++ < dist)
// 	{
// 		ix = center_x + (int)(distance * data->cosine);	// As for image coordinates, right is still plus positive and left is still negative
// 		iy = center_y - (int)(distance * data->sine); // As for image coordinates, up is negative/decrement and down is positive/increment
// 		mlx_put_pixel(rays->rays, ix, iy, RED);
// 	}
// }
