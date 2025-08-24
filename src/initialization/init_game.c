/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/24 14:27:08 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		init_game_elements(t_game *game, char *arg);

static void	init_game(t_game *game);
static void	init_minimap(t_game *game, char *path_to_map);
static void	init_player(t_game *game);
static void update_game_data_after_parsing(t_data *data);


void	init_game_elements(t_game *game, char *arg)
{
	init_game(game);
	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc failed", EXIT_FAILURE);
	game->player = get_player();
	if (!game->player)
		exit_early(game, "player malloc failed", EXIT_FAILURE);
	init_minimap(game, arg);
	init_player(game);
}

static void	init_game(t_game *game)
{
	t_data	*data;

	*game = (t_game){
		.background_inst_id = -1, .img3D_inst_id = -1,
		// .gun_inst_id = -1,
	};
	data = get_data();
	if (!data)
		exit_early(game, "Scales malloc failed", EXIT_FAILURE);
	game->data = data;
	game->mlx = mlx_init(data->wind_w, data->wind_h, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->background = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->background)
		exit_early(game, "background_img: mlx_new_image", EXIT_FAILURE);
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

	// test_print_data();			// !! extra utility, to be removed later
	
	parse_game_data(game, path_to_map);
	update_game_data_after_parsing(data);
	init_background(game);
	test_print_data(); 				// !! extra utility, to be removed later
	create_image_array(map, data);
	map->image = mlx_new_image(game->mlx, data->mmp_w, data->mmp_h);
	if (!map->image)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);

	// test elements ----
	map->test = mlx_new_image(game->mlx, data->mmp_w, data->mmp_h);
	if (!map->test)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);

	printf("%d	x	%d\n", data->mmp_w, data->mmp_h);	
	map_array_printer(map, 1);	// !! extra utility, to be removed later
	// write_img_array(0, 0);
	// ------------------

	map->game = game;
	map->player = game->player;
}

// Update function to update data fields not done by the parser
static void update_game_data_after_parsing(t_data *data)
{
	data->cosine = cos(data->cur_dir);
	data->sine = sin(data->cur_dir);
	data->mmp_w = data->tiles_x * data->tile_size;
	data->mmp_h = data->tiles_y * data->tile_size;
	data->pl_center_x = data->pl_posx + data->tile_size / 2;
	data->pl_center_y = data->pl_posy + data->tile_size / 2;
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
		exit_early(game, "blob_img: mlx_new_image failed", EXIT_FAILURE);
	pl->view = mlx_new_image(game->mlx, data->mmp_w, data->mmp_h);
	if (!pl->view)
		exit_early(game, "view_img: mlx_new_image failed", EXIT_FAILURE);
	pl->rays = get_rays();
	if (!pl->rays)
		exit_early(game, "rays malloc failed", EXIT_FAILURE);
	init_rays(pl->rays);
	pl->game = game;
	pl->map = game->map;
}
