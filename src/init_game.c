/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 20:28:08 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game_elements(t_game *game, char *arg);

static void	init_game(t_game *game);
static void	init_minimap(t_game *game, char *path_to_map);
static void	init_player(t_game *game);
static void	init_rays(t_game *game);


void	init_game_elements(t_game *game, char *arg)
{
	init_game(game);

	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc failed", EXIT_FAILURE);
	game->player = get_player();
	if (!game->player)
		exit_early(game, "player malloc failed", EXIT_FAILURE);
	game->rays = get_rays();
	if (!game->rays)
		exit_early(game, "rays malloc failed", EXIT_FAILURE);

	init_minimap(game, arg);
	init_player(game);
	init_rays(game);
}

static void	init_game(t_game *game)
{	
	t_data	*data;

	*game = (t_game){
		.img3D_inst_id = -1,
		// .gun_inst_id = -1,
	};
	data = get_data();
	if (!data)
		exit_early(game, "Scales malloc failed", EXIT_FAILURE);

	game->data = data;
	game->mlx = mlx_init(data->wind_w, data->wind_h, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img3D = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);
}

static void	init_minimap(t_game *game, char *path_to_map)
{
	t_data	*data;
	t_map	*map;

	data = game->data;
	map = game->map;

	map->data = data;
	map->image = mlx_new_image(game->mlx, data->mmp_w, data->mmp_h);
	if (!map->image)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);

	// this block may be removed after merging with parsing, maybe replaced with sth else
	map->fd = open(path_to_map, O_RDONLY);
	if (map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	parse_minimap(map);			// Later to be replaced with proper parsing or removed as this may be carried out during parsing the whole scene file
	map_array_printer(map, 1);	// extra utility, to be removed later

	map->game = game;
	map->player = game->player;
	map->rays = game->rays;
}

static void	init_player(t_game *game)
{
	t_data		*data;
	t_player	*pl;

	data = game->data;
	pl = game->player;


	pl->data = data;
	pl->blob2D = mlx_new_image(game->mlx, data->tile_size, data->tile_size);
	if (!pl->blob2D)
		exit_early(game, "player_img: mlx_new_image failed", EXIT_FAILURE);
	
	pl->game = game;
	pl->map = game->map;
	pl->rays = game->rays;
}

static void	init_rays(t_game *game)
{
	t_data	*data;
	t_rays	*rays;

	data = game->data;
	rays = game->rays;
	
	rays->data = data;
	rays->rays = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!rays->rays)
		exit_early(game, "rays_img: mlx_new_image failed", EXIT_FAILURE);

	rays->game = game;
	rays->map = game->map;
	rays->player = game->player;
}
