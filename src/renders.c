/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/06 22:55:19 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_overview(t_game *game, char *path_to_map);
static void	place_block(t_game *game, int hor, int vert, bool block);

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
				place_block(game, i, j, 1);
			else
				place_block(game, i, j, 0);
			// usleep(200);
			// if (mlx_image_to_window(game->mlx, game->map->overview, 0, 0) < 0)
			// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
		}
		map_layer = get_next_line(game->map->fd);
		j++;
	}
}
 
static void	place_block(t_game *game, int hor, int vert, bool block)
{
	int	i;
	int	j;
	int	color;

	if (block)
		color = STONE_GRAY;
	else
		color = WHITE;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(game->map->overview, hor * BLOCK_SIZE + i,
				vert * BLOCK_SIZE + j, color);
	}
}
