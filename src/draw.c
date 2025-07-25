/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/23 20:25:29 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		draw_map(t_game *game);

static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int color);

static void	place_block2(t_img *img, int i, int j, int block_color, int bls);
static void	draw_border2(t_img *img, int	width, int height, int color, int bls);

static void	draw_player_direction(t_map *map);

// void	draw_map(t_game *game)
// {
// 	char	*map_layer;
// 	int		i;
// 	int		j;

// 	map_layer = get_next_line(game->map->fd);
// 	if (!map_layer)
// 		exit_early(game, "map_layer: gnl", EXIT_FAILURE);
// 	i = -1;
// 	j = 0;
// 	while (map_layer)
// 	{
// 		i = -1;
// 		while (*(map_layer + ++i))
// 		{
// 			if (*(map_layer + i) == '1')
// 				place_block(game->map->image, i, j, STONE_GRAY);
// 			else if (*(map_layer + i) == '0')
// 				place_block(game->map->image, i, j, 0);
// 		}
// 		free(map_layer);
// 		map_layer = get_next_line(game->map->fd);
// 		j++;
// 	}
// 	draw_border(game->img3D, WIDTH, HEIGHT, CYAN);
// 	draw_border(game->map->image, MAP_W, MAP_H, SAND_YELLOW);
// 	draw_border2(game->player->blob2D, TILE_SIZE, TILE_SIZE, RED, 1);
// 	place_player2D_2(game, 1);
// }

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
	draw_player_direction(game->map);
	draw_border(game->img3D, data->wind_w, data->wind_h, CYAN);
	// draw_border(game->map->image, MAP_W, MAP_H, SAND_YELLOW);
	draw_border2(game->player->blob2D, data->tile_size, data->tile_size, RED, 1);
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

	if (!block_color)
		return ;
	j = -1;
	while (++j < TILE_SIZE)
	{
		i = -1;
		while (++i < TILE_SIZE)
			mlx_put_pixel(img, x * TILE_SIZE + i, y * TILE_SIZE + j,
					block_color);
	}
}

static void	draw_border(t_img *img, int width, int height, int color)
{
	int i;
	int	j;
	int	block_x;
	int	block_y;

	i = -1;
	j = -1;
	block_x = width / TILE_SIZE;
	block_y = height / TILE_SIZE;
	while (++j < block_y)
	{
		i = -1;
		if (j == 0 || j == (block_y - 1))
		{
			while (++i < block_x)
				place_block(img, i, j, color);
		}
		else
		{
			while (++i < block_x)
			{
				if (i == 0 || i == (block_x - 1))
					place_block(img, i, j, color);	
			}
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

static void	draw_border2(t_img *img, int width, int height, int color, int bls)
{
	int i;
	int	j;
	int	block_x;
	int	block_y;

	i = -1;
	j = -1;
	block_x = width / bls;
	block_y = height / bls;
	while (++j < block_y)
	{
		i = -1;
		if (j == 0 || j == (block_y - 1))
		{
			while (++i < block_x)
				place_block2(img, i, j, color, bls);
		}
		else
		{
			while (++i < block_x)
			{
				if (i == 0 || i == (block_x - 1))
					place_block2(img, i, j, color, bls);	
			}
		}
	}
}

/*
Function to draw the player direction as a line extending from the center of
the player blob, but by only updating the instance with the line orientation and
not redrawing the whole blob image.
  - distance = x * sqrt(1 + tan * tan)
*/
static void	draw_player_direction(t_map *map)
{
	int		center_x;
	int		center_y;
	double	distance;
	double	x;
	double	y;
	int		ix;
	int		iy;
	double	angle;

	double	sine;
	double	cosine;

	angle = (double)map->data->cur_dir;
	// angle = PI / 4;
	sine = sin(angle);
	cosine = cos(angle);
	center_x = TILE_SIZE / 2;
	center_y = TILE_SIZE / 2;
	distance = 0;
	while (distance++ < 8)
	{
		x = distance * cosine;
		y = distance * sine;
		ix = center_x + (int)x;	// As for image coordinates, right is still plus positive and left is still negative
		iy = center_y - (int)y; // As for image coordinates, up is negative/decrement and down is positive/increment
		mlx_put_pixel(map->player->blob2D, ix, iy, RED);
	}
}
