/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/11 18:17:45 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		draw_map(t_game *game);

static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int color);

static void	place_block2(t_img *img, int i, int j, int block_color, int bls);
static void	draw_border2(t_img *img, int	width, int height, int color, int bls);

void	draw_map(t_game *game)
{
	char	*map_layer;
	int		i;
	int		j;

	map_layer = get_next_line(game->map->fd);
	if (!map_layer)
		exit_early(game, "map_layer: gnl", EXIT_FAILURE);
	i = -1;
	j = 0;
	while (map_layer)
	{
		i = -1;
		while (*(map_layer + ++i))
		{
			if (*(map_layer + i) == '1')
				place_block(game->map->image, i, j, STONE_GRAY);
			else if (*(map_layer + i) == '0')
				place_block(game->map->image, i, j, 0);
		}
		free(map_layer);
		map_layer = get_next_line(game->map->fd);
		j++;
	}
	draw_border(game->img3D, WIDTH, HEIGHT, CYAN);
	draw_border(game->map->image, MAP_W, MAP_H, SAND_YELLOW);
	draw_border2(game->player->blob2D, BLOCK_SIZE, BLOCK_SIZE, RED, 1);
	place_player2D_2(game, 1);
}

/*
Function to place a block/tile of size as defined in the HEADER as BLOCK_SIZE
  - if block color is provided as 0, then block_color will be white
  - x and y are the starting coordinates (from upper left corner) of blocks in a
  	tiled world representing the whole block of several pixels BLOCK_SIZE in 
	width and height
*/
static void	place_block(t_img *img, int x, int y, int block_color)
{
	int		i;
	int		j;

	if (!block_color)
		return ;
	// if (!block_color)
	// 	block_color = BLACK ;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(img, x * BLOCK_SIZE + i, y * BLOCK_SIZE + j,
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
	block_x = width / BLOCK_SIZE;
	block_y = height / BLOCK_SIZE;
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
