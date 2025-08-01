/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/01 03:42:41 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		init_graphics_rendering(void *param);

// static void render_background(t_game *game);
static void render_3dview(t_game *game);
static void render_minimap(t_game *game, t_map *map);
static void	render_player_blob(t_game *game, t_player *pl);
static void render_player_2dview(t_game *game, t_player *pl);

void	init_graphics_rendering(void *param)
{
	t_game		*game;
	t_map		*map;
	t_player	*pl;
	t_rays		*rays;

	game = (t_game *)param;
	map = game->map;
	pl = game->player;

	// render_background(game);    // Render background first
	render_3dview(game);
	render_minimap(game, map);
	render_player_blob(game, pl);
	render_player_2dview(game, pl);
}

/*
 * BACKGROUND RENDERING GUIDE - Implementation by GitHub Copilot
 *
 * This function renders the background image to the window.
 * It should be called FIRST in the rendering pipeline to appear behind other elements.
 *
 * HOW IT WORKS:
 * 1. Check if background is already rendered (background_inst_id == -1)
 * 2. Use mlx_image_to_window() to display the background image
 * 3. Position it at (0, 0) to cover the entire window
 * 4. Store the instance ID for later reference
 * 5. Handle errors if rendering fails
 *
 * IMPORTANT: This must be called before other render functions to act as background layer
 */
/*
static void render_background(t_game *game)
{
	if (game->background_inst_id == -1)
	{
		game->background_inst_id = mlx_image_to_window(game->mlx, game->background,
				0, 0);
		if (game->background_inst_id < 0)
			exit_early(game, "background_image: mlx_image_to_window", EXIT_FAILURE);
	}
}
*/

static void render_3dview(t_game *game)
{
	if (game->img3D_inst_id == -1)
	{
		game->img3D_inst_id = mlx_image_to_window(game->mlx, game->img3D,
				0, 0);
		if (game->img3D_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void render_minimap(t_game *game, t_map *map)
{
	t_data	*data;

	data = game->data;

	if (map->image_inst_id == -1)
	{
		map->image_inst_id = mlx_image_to_window(game->mlx, map->image,
			data->mmp_offx, data->mmp_offy);
		if (map->image_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void	render_player_blob(t_game *game, t_player *pl)
{
	t_data	*data;

	data = game->data;
	if (pl->blob_inst_id == -1)
	{
		pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob2D,
				data->pl_posx + data->mmp_offx, data->pl_posy + data->mmp_offy);
		if (pl->blob_inst_id < 0)
			exit_early(game, "blob2D: mlx_image_to_window", EXIT_FAILURE);
	}
	else
	{
		pl->blob2D->instances[pl->blob_inst_id].x = data->pl_posx +
				data->mmp_offx;
		pl->blob2D->instances[pl->blob_inst_id].y = data->pl_posy +
				data->mmp_offy;
	}
}

static void render_player_2dview(t_game *game, t_player *pl)
{
	t_data	*data;

	data = game->data;

	if (pl->view_inst_id == -1)
	{
		printf("here it is\n");

		pl->view_inst_id = mlx_image_to_window(game->mlx, pl->view,
			data->mmp_offx, data->mmp_offy);
		if (pl->view_inst_id < 0)
			exit_early(game, "2Dview_img: mlx_image_to_window", EXIT_FAILURE);
	}
}
