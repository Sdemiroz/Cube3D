/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/09 21:51:37 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		render_overview(t_game *game, char *path_to_map);
// static void	place_block(int hor, int vert, int block_color, int offset);
static void	place_block(t_img *img, int *coords, int block_color, int offset);
static void	draw_border(t_img *img, int	width, int height, int color);


void	render_overview(t_game *game, char *path_to_map)
{
	char	*map_layer;
	int		i;
	int		j;
	int		coords[2];
	
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
			coords[0] = i;
			coords[1] = j;
			if (*(map_layer + i) == '1')
				place_block(game->map->overview, coords, STONE_GRAY, 1);
			else if (*(map_layer + i) == '0')
				place_block(game->map->overview, coords, 0, 1);
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
  - if offset = 0, no offset is used
  - if offset = 1, the offset of the map wil be used i.e. MAP_OFFSET_(X, Y)
  - any other value of offset may be later used to add functionality of the fn
  - i and j are block numbers/counters in a tiled world representing the whole
	block of several pixels BLOCK_SIZE in width and height
*/
static void	place_block(t_img *img, int *coords, int block_color, int offset)
{
	t_game	*game;
	int		i;
	int		j;
	int		off[2];

	game = get_game();
	if (offset == 1)
	{
		off[0] = MAP_OFFSET_X;
		off[1] = MAP_OFFSET_Y;
	}
	else
	{
		off[0] = 0;
		off[1] = 0;
	}
	if (!block_color)
		block_color = WHITE;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(img, coords[0] * BLOCK_SIZE + i + off[0],
				coords[1] * BLOCK_SIZE + j + off[1], block_color);
	}
}

static void	draw_border(t_img *img, int	width, int height, int color)
{
	int coords[2];
	int	block_x;
	int	block_y;

	coords[0] = -1;
	coords[1] = -1;
	block_x = width / BLOCK_SIZE;
	block_y = height / BLOCK_SIZE;
	
	while (++(coords[1]) < block_y)
	{
		if (coords[1] == 0 || coords[1] == block_y - 1)
		{
			while (++(coords[0]) < block_x)
				place_block(img, coords, color, 0);
		}
		else
		{
			while (++(coords[0]) < block_x)
			{
				if (coords[0] == 0 || coords[0] == block_x - 1)
					place_block(img, coords, color, 0);
			}
		}
	}
}
