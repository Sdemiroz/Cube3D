/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/24 14:45:28 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		init_graphics_rendering(void *param);

static void inline render_background(t_game *game);
static void inline render_3dview(t_game *game);
static void inline render_minimap(t_game *game, t_map *map);
static void	render_player_blob(t_game *game, t_player *pl);
static void inline render_player_2dview(t_game *game, t_player *pl);

// test image
static void inline render_test_image(t_game *game, t_map *map);


void	init_graphics_rendering(void *param)
{
	t_game		*game;
	t_map		*map;
	t_player	*pl;

	game = (t_game *)param;
	map = game->map;
	pl = game->player;

	render_background(game);
	render_3dview(game);
	render_minimap(game, map);

	// test image ----
	render_test_image(game, map);
	// ---------------

	render_player_2dview(game, pl);
	render_player_blob(game, pl);
}

static void inline	render_background(t_game *game)
{
	if (game->background_inst_id == -1)
	{
		game->background_inst_id = mlx_image_to_window(game->mlx, game->background,
				0, 0);
		if (game->background_inst_id < 0)
			exit_early(game, "background_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void inline render_3dview(t_game *game)
{
	if (game->img3D_inst_id == -1)
	{
		game->img3D_inst_id = mlx_image_to_window(game->mlx, game->img3D,
				0, 0);
		if (game->img3D_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}

	// TODO: Call the 3D wall rendering function to draw textured walls
	render_3d_walls(game);
}

static void inline render_minimap(t_game *game, t_map *map)
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
	// int		center_offset;

	data = game->data;
	// center_offset = data->tile_size / 2;
	// center_offset = 0;
	// if (pl->blob_inst_id == -1)
	// {
	// 	pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob2D,
	// 			data->pl_posx + data->mmp_offx - center_offset, 
	// 			data->pl_posy + data->mmp_offy - center_offset);
	// 	if (pl->blob_inst_id < 0)
	// 		exit_early(game, "blob2D: mlx_image_to_window", EXIT_FAILURE);
	// }
	// else
	// {
	// 	pl->blob2D->instances[pl->blob_inst_id].x = data->pl_posx +
	// 			data->mmp_offx - center_offset;
	// 	pl->blob2D->instances[pl->blob_inst_id].y = data->pl_posy +
	// 			data->mmp_offy - center_offset;
	// }
	if (pl->blob_inst_id == -1)
	{
		pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob2D,
				data->pl_posx + data->mmp_offx, 
				data->pl_posy + data->mmp_offy);
		if (pl->blob_inst_id < 0)
			exit_early(game, "blob2D: mlx_image_to_window", EXIT_FAILURE);
	}
	else
	{
		// Player blob in its intended positions
		pl->blob2D->instances[pl->blob_inst_id].x = data->pl_posx +
				data->mmp_offx;
		pl->blob2D->instances[pl->blob_inst_id].y = data->pl_posy +
				data->mmp_offy;

		// // Player blob up-left shifted by half a tile_size (when offset_dimn.s == tile_size)
		// pl->blob2D->instances[pl->blob_inst_id].x = data->pl_posx +
		// 		data->mmp_offx / 2;
		// pl->blob2D->instances[pl->blob_inst_id].y = data->pl_posy +
		// 		data->mmp_offy / 2;
	}
}

static void inline render_player_2dview(t_game *game, t_player *pl)
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
	else
	{
		// // 0 to 90 is good -> verified
		// pl->view->instances[pl->view_inst_id].x = data->mmp_offx + data->debug_offset_x;
		// pl->view->instances[pl->view_inst_id].y = data->debug_offset_y;
		
		// // 90 to 180 is good -> verified
		// pl->view->instances[pl->view_inst_id].x = data->debug_offset_x;
		// pl->view->instances[pl->view_inst_id].y = data->debug_offset_y;
		
		// // 180 to 270 is good -> verified
		// pl->view->instances[pl->view_inst_id].x = data->debug_offset_x;
		// pl->view->instances[pl->view_inst_id].y = data->mmp_offy + data->debug_offset_y;
		
		// 270 to 360 is good -> verified (this is the normal one)
		pl->view->instances[pl->view_inst_id].x = data->mmp_offx + data->debug_offset_x;
		pl->view->instances[pl->view_inst_id].y = data->mmp_offy + data->debug_offset_y;
		
		// // 0 to 360 is partially good but map seems shrunken or ray_length is half a tile_size shorter in all directions-> verified
		// pl->view->instances[pl->view_inst_id].x = data->mmp_offx / 2 + data->debug_offset_x;
		// pl->view->instances[pl->view_inst_id].y = data->mmp_offy / 2 + data->debug_offset_y;
		
	}
}


// test image rendering function --------
static void inline render_test_image(t_game *game, t_map *map)
{
	t_data	*data;

	data = game->data;
	
	if (map->test_inst_id == -1)
	{
		map->test_inst_id = mlx_image_to_window(game->mlx, map->test,
			data->mmp_offx, data->mmp_offy);
		if (map->test_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}
