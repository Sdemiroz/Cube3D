/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/09 22:23:39 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		render_overview(t_game *game, char *path_to_map);
// static void	place_block(int hor, int vert, int block_color, int offset);
static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int color);


void	render_overview(t_game *game, char *path_to_map)
{
	char	*map_layer;
	int		i;
	int		j;
	
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
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
				place_block(game->map->overview, i, j, STONE_GRAY);
			else if (*(map_layer + i) == '0')
				place_block(game->map->overview, i, j, 0);
			// usleep(200);
			// if (mlx_image_to_window(game->mlx, game->map->overview, 0, 0) < 0)
			// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
		}
		free(map_layer);
		map_layer = get_next_line(game->map->fd);
		j++;
	}
	draw_border(game->map->overview, MAP_W, MAP_H, RED);
	// (void)&draw_border;
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
	t_game	*game;
	int		i;
	int		j;

	game = get_game();
	if (!block_color)
		block_color = WHITE;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(img, x * BLOCK_SIZE + i, y * BLOCK_SIZE + j,
					block_color);
	}
}

static void	draw_border(t_img *img, int	width, int height, int color)
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
		if (j == 0 || j == (block_y - 1))
		{
			while (++i < block_x)
				place_block(img, i, j, color);
		}
		else
		{
			while (++(i) < block_x)
			{
				if (i == 0 || i == (block_x - 1))
					place_block(img, i, j, color);
			}
		}
	}
}
