/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/27 16:57:35 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		render_map(void *param);

static void render_3D_instance(t_game *game);
static void render_map_instance(t_game *game, t_map *map);
static void	render_player_blob_instance(t_game *game, t_player *pl);
static void render_rays_instance(t_game *game, t_rays *rays);

void	render_map(void *param)
{
	t_game		*game;
	t_map		*map;
	t_player	*pl;
	t_rays		*rays;

	game = (t_game *)param;
	map = game->map;
	pl = game->player;
	rays = game->rays;

	render_3D_instance(game);
	render_map_instance(game, map);
	render_player_blob_instance(game, pl);
	render_rays_instance(game, rays);
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

static void	render_player_blob_instance(t_game *game, t_player *pl)
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

static void render_rays_instance(t_game *game, t_rays *rays)
{
	t_data	*data;

	data = game->data;
	
	if (rays->rays_inst_id == -1)
	{
		rays->rays_inst_id = mlx_image_to_window(game->mlx, rays->rays,
			data->mmp_offx, data->mmp_offy);
		if (rays->rays_inst_id < 0)
			exit_early(game, "rays_img: mlx_image_to_window", EXIT_FAILURE);
	}
}
