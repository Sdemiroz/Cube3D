/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/30 19:17:07 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		draw_map(t_game *game);

static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int thickness);

static void	place_block2(t_img *img, int i, int j, int block_color, int bls);
static void	draw_border2(t_img *img, int	width, int height, int color, int bls);

void	draw_map(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	char		**map;
	int			i;
	int			j;

	data = game->data;
	pl = game->player;
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
	draw_border(game->img3D, data->wind_w, data->wind_h, data->tile_size);
	// draw_border(game->map->image, data->mmp_w, data->mmp_h, data->tile_size);
	// draw_border2(game->map->image, data->mmp_w, data->mmp_h, SAND_YELLOW, 5);
	// draw_border2(game->player->blob2D, data->tile_size, data->tile_size, LAVA_RED_DARK, 1);
	draw_current_fov(pl, pl->rays);
	place_player2D_2(game);
	draw_player_direction(game->player, data);
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

// static void	place_block(t_img *img, int x, int y, int block_color)
// {
// 	int		i;
// 	int		j;
// 	t_data	*data;

// 	if (!block_color)
// 		return ;
// 	data = get_data();
// 	j = -1;
// 	while (++j < data->tile_size)
// 	{
// 		i = -1;
// 		while (++i < data->tile_size)
// 		{
// 			mlx_put_pixel(img, x * data->tile_size + i,
// 					y * data->tile_size + j, block_color);
// 		}
// 	}
// }

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
			while (++i < block_x)
				place_block2(img, i, j, color, bls);
		else
		{
			while (++i < block_x)
				if (i == 0 || i == (block_x - 1))
					place_block2(img, i, j, color, bls);	
		}
	}
}
