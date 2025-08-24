/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:44:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/24 17:05:03 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	place_block(t_img *img, int i, int j, int block_color);
void	place_block2(t_img *img, int i, int j, int block_color, int bls);
void	place_lined_block(t_img *img, int x, int y, int block_color);

/*
Function to place a block/tile of size as defined in the HEADER as TILE_SIZE
  - if block color is provided as 0, then block_color will be white
  - x and y are the starting coordinates (from upper left corner) of blocks in a
  	tiled world representing the whole block of several pixels TILE_SIZE in 
	width and height
  - the final row and column of the block is not drawn to provide a checkered
    pattern
*/
void	place_block(t_img *img, int x, int y, int block_color)
{
	int		i;
	int		j;
	int		tile_size;

	if (!block_color)
		return ;
	tile_size = get_data()->tile_size;
	j = -1;
	while (++j < tile_size)
	{
		if (j == tile_size - 1)
			break ;
		else
		{
			i = -1;
			while (++i < tile_size)
			{
				if (i == tile_size - 1)
					break ;
				mlx_put_pixel(img, x * tile_size + i,
						y * tile_size + j, block_color);
			}
		}
	}
}

// /*
// Function to place a block/tile of size as defined in the HEADER as TILE_SIZE
//   - if block color is provided as 0, then block_color will be white
//   - x and y are the starting coordinates (from upper left corner) of blocks in a
//   	tiled world representing the whole block of several pixels TILE_SIZE in 
// 	width and height
// */
// void	place_block(t_img *img, int x, int y, int block_color)
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

// bls = TILE_SIZE 
void	place_block2(t_img *img, int x, int y, int block_color, int bls)
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

void	place_lined_block(t_img *img, int x, int y, int block_color)
{
	int		i;
	int		j;
	int		tile_size;
	int		border;

	// border = 0;
	border = BLACK;
	tile_size = get_data()->tile_size;
	j = -1;
	while (++j < tile_size)
	{
		i = -1;
		while (++i < tile_size)
		{
			if (j == 0 || j == tile_size - 1)
				mlx_put_pixel(img, x * tile_size + i,
						y * tile_size + j, border);
			else if (i == 0 || i == tile_size - 1)
				mlx_put_pixel(img, x * tile_size + i,
						y * tile_size + j, border);
			else
				mlx_put_pixel(img, x * tile_size + i,
						y * tile_size + j, block_color);
		}
	}
}
