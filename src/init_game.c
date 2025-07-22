/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/22 21:01:19 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*init_game_elements(t_game *game, char *arg);

static void	init_game(t_game *game);
static void	init_data(t_game *game);
static void	init_minimap(t_game *game, char *path_to_map);
static void	init_player(t_game *game);


t_game	*init_game_elements(t_game *game, char *arg)
{
	init_game(game);
	init_minimap(game, arg);
	init_player(game);
	
	// read_input(game);
	// write_to_map_array(game);
	
	return (game);
}

static void	init_game(t_game *game)
{	
	t_data	*data;

	*game = (t_game){
		.img3D_inst_id = -1,	// Initialize 3D image instance ID to -1		// Initialize player pointer to NULL
	};
	init_data(game);
	data = game->data;
	game->mlx = mlx_init(data->wind_w, data->wind_h, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img3D = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);
}

static void	init_data(t_game *game)
{
	game->data = malloc(sizeof(t_data));
	if (!game->data)
		exit_early(game, "Scales malloc failed", EXIT_FAILURE);
	*game->data = (t_data){
		.wind_w = WIDTH,
		.wind_h = HEIGHT,
		.pl_dia = PLAYER_DIA,
		.pl_posx = START_PX,
		.pl_posy = START_PY,
		.pl_fov = FOV,
		.pl_rays = NUM_RAYS,
		.tile_size = TILE_SIZE,
		.minimap_w = MAP_W,
		.minimap_h = MAP_H,
		.tiles_x = MAP_W / TILE_SIZE,
		.tiles_y = MAP_H / TILE_SIZE,
		.pl_ini_dir = 'N',
		.pl_dir = PI / 2,
		.minimap_offx = MAP_OFFSET_X,
		.minimap_offy = MAP_OFFSET_Y,
		.minimap_scale = MAP_SCALE,
	};
}

static void	init_minimap(t_game *game, char *path_to_map)
{
	t_data	*data;
	t_map		*map;

	data = game->data;
	map = malloc(sizeof(t_map));
	if (!map)
		exit_early(game, "map: struct malloc failed", 1);
	*map = (t_map){
		.image_inst_id = -1,
		.fd = -1,
	};
	map->image = mlx_new_image(game->mlx, MAP_W, MAP_H);
	if (!map->image)
		exit_early(game, "map_image: mlx_new_image failed", EXIT_FAILURE);
	map->fd = open(path_to_map, O_RDONLY);
	if (map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	parse_minimap(game, map);	// Later to be replaced with proper parsing or removed as this may be carried out during parsing the whole scene file
		
	map_array_printer(1);	// extra utility, to be removed later
}

static void	init_player(t_game *game)
{
	game->player = get_player();
	if (!game->player)
		exit_early(game, "game_player: malloc\n", 1);
	game->map->player = game->player;
	game->player->blob2D = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
}


/*
void	init_shell(t_shell *shl, int ac, char **av, char **envp)
{
	*shl = (t_shell){
		.ac = ac,
		.av = av,
		.stdio[0] = dup(STDIN_FILENO),
		.stdio[1] = dup(STDOUT_FILENO),
		.shlvl = 1,
		.tmp_file_fd = -1
	};
	if (shl->stdio[0] < 0 || shl->stdio[1] < 0)
	{
		if (shl->stdio[1] != -1)
			close(shl->stdio[1]);
		if (shl->stdio[0] != -1)
			close(shl->stdio[0]);
		exit_early(NULL, NULL, ERRMSG_DUP);
	}
	init_environ_variables(shl, envp);
	update_shlvl(shl);
	shl->cwd = getcwd(NULL, 0);
	if (!shl->cwd)
		exit_early(shl, NULL, "getcwd");
	set_prompt(shl, "", " % ");
}


*/