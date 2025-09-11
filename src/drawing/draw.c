/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/09/10 18:41:35 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		start_drawing(t_game *game);

static void	draw_minimap(t_game *game, char **map);
// static void	draw_border(t_img *img, int	width, int height, int thickness);
// static void	draw_border2(t_img *img, int	width, int height, int color, int bls);


void	start_drawing(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	char		**map;

	data = game->data;
	pl = game->player;
	map = game->map->map_array;

	cast_rays(pl->map, pl->rays, data);
	erase_3d_walls(game);
	draw_3d_walls(game);
	draw_minimap(game, map);
	draw_current_fov(pl, pl->rays);
	place_player2D_2(game);
	draw_player_direction(game->player, data);
}

static void	draw_minimap(t_game *game, char **map)
{
	int	i;
	int	j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == '1')
				place_lined_block(game->map->image, i, j, STONE_GRAY);
			else if (map[j][i] == '0' || is_valid(map[j][i]))
				place_lined_block(game->map->image, i, j, DARK_GRAY);
				// place_lined_block(game->map->image, i, j, 0);
		}
	}
}

// static void	draw_border(t_img *img, int width, int height, int thickness)
// {
// 	int i;
// 	int	j;
// 	int	block_x;
// 	int	block_y;

// 	block_x = width / thickness;
// 	block_y = height / thickness;
// 	j = -1;
// 	while (++j < block_y)
// 	{
// 		i = -1;
// 		if (j == 0 || j == (block_y - 1))
// 			while (++i < block_x)
// 				place_block(img, i, j, LAVA_RED_DARK);
// 		else
// 		{
// 			while (++i < block_x)
// 				if (i == 0 || i == (block_x - 1))
// 					place_block(img, i, j, LAVA_RED_DARK);
// 		}
// 	}
// }

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
