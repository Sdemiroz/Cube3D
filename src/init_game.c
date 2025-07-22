/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/22 17:50:40 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*init_game_elements(t_game *game, char *arg);

static void	init_game(t_game *game);
static void	init_minimap(t_game *game, char *path_to_map);
static void	init_player(t_game *game);
static void	parse_minimap(t_game *game, t_map *map);
static void	write_to_map_array(t_map *map, char ***geo, char *nxtline);
static void	assign_direction(t_map *map, char player_dir);

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
	*game = (t_game){
		.img3D_inst_id = -1,	// Initialize 3D image instance ID to -1		// Initialize player pointer to NULL
	};
	
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);

	// rectangular frame for player blob
}

static void	init_minimap(t_game *game, char *path_to_map)
{
	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc", 1);
	game->map->image = mlx_new_image(game->mlx, MAP_W, MAP_H);
	if (!game->map->image)
		exit_early(game, "map_image: mlx_new_image", EXIT_FAILURE);
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	parse_minimap(game, game->map);
	
	map_array_printer(1);
}

static void	init_player(t_game *game)
{
	game->player = get_player();
	if (!game->player)
		exit_early(game, "game_player: malloc\n", 1);
	game->map->player = game->player;
	game->player->blob2D = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
}

static void	parse_minimap(t_game *game, t_map *map)
{
	char	**geometry;
	char	*next_line;
	int		i;

	geometry = malloc(map->vert_blocks * sizeof(char *) + 1);
	if (!geometry)
		exit_early(game, "malloc error for map geometry", EXIT_FAILURE);
	geometry[map->vert_blocks] = NULL;
	i = -1;
	while (++i < map->vert_blocks)
	{
		geometry[i] = malloc(map->horiz_blocks * sizeof(char) + 1);
		if (!geometry[i])
			exit_early(game, "malloc error for map geometry row", EXIT_FAILURE);
		ft_memset(geometry[i], 32, map->horiz_blocks);	// filling up the whole string with spaces (' ' - ascii value 32)
		geometry[i][map->horiz_blocks] = '\0';			// null termination at the end of each string
	}
	next_line = get_next_line(map->fd);
	if (!next_line)
		exit_early(game, "gnl", EXIT_FAILURE);
	write_to_map_array(map, &geometry, next_line);
	map->map_array = geometry;
}

static void	write_to_map_array(t_map *map, char ***geo, char *nxtline)
{
	int		i;
	int		j;
	char	**geometry;
	
	geometry = *geo;
	i = -1;
	while (++i < map->vert_blocks)
	{
		j = -1;
		while (nxtline && ++j < map->horiz_blocks)
		{
			if (is_valid_block(nxtline[j]))
			{
				geometry[i][j] = nxtline[j];
				if (is_player(nxtline[j]))
				{
					map->pl_posx = j * TILE_SIZE;
					map->pl_posy = i * TILE_SIZE;
					assign_direction(map, nxtline[j]);
				}
			}
		}
		free(nxtline);
		nxtline = get_next_line(map->fd);
	}
}

static void	assign_direction(t_map *map, char player_dir)
{
	map->pl_dir_initial = player_dir;
	if (player_dir == 'E')
		map->pl_dir = 0;		// 0 degrees in radians
	else if (player_dir == 'N')
		map->pl_dir = PI / 2;	// 90 degrees in radians
	else if (player_dir == 'W')
		map->pl_dir = PI;		// 180 degrees in radians
	else if (player_dir == 'S')
		map->pl_dir = -PI / 2;	// 270 or -90 degrees in radians
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