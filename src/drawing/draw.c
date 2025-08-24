/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/23 16:34:43 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		start_drawing(t_game *game);

static void	draw_minimap(t_game *game, char **map);
static void	draw_border(t_img *img, int	width, int height, int thickness);
// static void	draw_border2(t_img *img, int	width, int height, int color, int bls);


void	start_drawing(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	char		**map;

	data = game->data;
	pl = game->player;
	map = game->map->map_array;

	draw_minimap(game, map);
	draw_border(game->img3D, data->wind_w, data->wind_h, data->tile_size);
	
	cast_rays(pl->map, pl->rays, data);
	
	// test image
	// draw_test_image();
	
	draw_current_fov(pl, pl->rays);
	
	place_player2D_2(game);
	// draw_border2(pl->blob2D, data->tile_size, data->tile_size, LAVA_RED_DARK, 1);
	
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
		}
	}
}

static void	draw_border(t_img *img, int width, int height, int thickness)
{
	int i;
	int	j;
	int	block_x;
	int	block_y;

	block_x = width / thickness;
	block_y = height / thickness;
	j = -1;
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
