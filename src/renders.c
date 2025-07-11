/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/11 19:00:57 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		render_map(void *param);

static void render_3D_instance(t_game *game);
static void render_map_instance(t_game *game, t_map *map);
static void	render_player_blob_instance(t_game *game, t_player *pl);

void	render_map(void *param)
{
	t_game		*game;
	t_map		*map;
	t_player	*pl;

	game = (t_game *)param;
	map = game->map;
	pl = game->player;
	
	render_3D_instance(game);
	render_map_instance(game, map);
	render_player_blob_instance(game, pl);
}

static void render_3D_instance(t_game *game)
{
	if (game->img3D_inst_id == -1)
	{
		game->img3D_inst_id = mlx_image_to_window(game->mlx, game->img3D,
				0, 0);
		if (game->img3D_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void render_map_instance(t_game *game, t_map *map)
{
	if (game->map->image_inst_id == -1)
	{
		game->map->image_inst_id = mlx_image_to_window(game->mlx, map->image,
				MAP_OFFSET_X, MAP_OFFSET_Y);
		if (map->image_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void	render_player_blob_instance(t_game *game, t_player *pl)
{
	if (pl->blob_inst_id == -1)
	{
		pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob2D,
				pl->pos_x + MAP_OFFSET_X, pl->pos_y + MAP_OFFSET_Y);
		if (pl->blob_inst_id < 0)
			exit_early(game, "blob2D: mlx_image_to_window", EXIT_FAILURE);
	}
	else
	{
		pl->blob2D->instances[pl->blob_inst_id].x = pl->pos_x + MAP_OFFSET_X;
		pl->blob2D->instances[pl->blob_inst_id].y = pl->pos_y + MAP_OFFSET_Y;
	}
}
