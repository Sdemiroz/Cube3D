/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/09 18:51:04 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_overview(t_game *game, char *path_to_map);
static void	place_block(int hor, int vert, bool block, int offset);

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
				place_block(i, j, 1, 1);
			else if (*(map_layer + i) == '0')
				place_block(i, j, 0, 1);
			// usleep(200);
			// if (mlx_image_to_window(game->mlx, game->map->overview, 0, 0) < 0)
			// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
		}
		free(map_layer);
		map_layer = get_next_line(game->map->fd);
		j++;
	}
}

/*
Function to place a block/tile of size as defined in the HEADER as BLOCK_SIZE
  - bool block is used to determine the color of the block placed
  - if offset = 0, no offset is used
  - if offset = 1, the offset of the map wil be used i.e. MAP_OFFSET_(X, Y)
  - any other value of offset may be later used to add functionality of the fn
*/
static void	place_block(int hor, int vert, bool block, int offset)
{
	t_game	*game;
	int		i;
	int		j;
	int		color;
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
	if (block)
		color = STONE_GRAY;
	else
		color = WHITE;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(game->map->overview, hor * BLOCK_SIZE + i + off[0],
				vert * BLOCK_SIZE + j + off[1], color);
	}
}

// static void	draw_border(t_img *img, int	width, int height, int color)
// {
// 	int x;
// 	int	y;

	

// }