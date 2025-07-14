/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/14 19:49:36 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*init_game(char *arg);

static void	set_game_elements(t_game *game, char *path_to_map);
static void	initialize_map2D(t_game *game, t_map *map);
static void	parse_map(t_map *map, char ***geo, char *nxtline);
static void	assign_direction(t_map *map, char player_dir);

t_game	*init_game(char *arg)
{
	t_game	*game;
	
	game = get_game();
	if(!game)
		exit_early(game, "Malloc error Game\n", 1);
	set_game_elements(game, arg);

	// read_input(game);
	// parse_map(game);
	return (game);
}

static void	set_game_elements(t_game *game, char *path_to_map)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);
	
	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc", 1);
	game->map->image = mlx_new_image(game->mlx, MAP_W, MAP_H);
	if (!game->map->image)
		exit_early(game, "map_image: mlx_new_image", EXIT_FAILURE);
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	initialize_map2D(game, game->map);
	
	write_map_colorful(game->map);		// print from parsed map
	print_map(game->map);	// print from parsed map
	print_map_colorful(game->map);	// print from parsed map
	
	game->player = get_player();
	if (!game->player)
		exit_early(game, "game_player: malloc\n", 1);
	game->map->player = game->player;
	// game->player->blob2D = mlx_new_image(game->mlx, PLAYER_DIA + 2, PLAYER_DIA + 2);
	game->player->blob2D = mlx_new_image(game->mlx, BLOCK_SIZE, BLOCK_SIZE);	// rectangular frame for player blob
}

// static void	initialize_map2D(t_game *game, t_map *map)
// {
// 	char	**geometry;
// 	char	*next_line;
// 	int		i;
// 	int		j;

// 	geometry = malloc(map->vert_blocks * sizeof(char *) + 1);
// 	if (!geometry)
// 		exit_early(game, "malloc error for map geometry", EXIT_FAILURE);
// 	geometry[map->vert_blocks] = NULL;
// 	i = -1;
// 	while (++i < map->vert_blocks)
// 	{
// 		geometry[i] = malloc(map->horiz_blocks * sizeof(char) + 1);
// 		if (!geometry[i])
// 			exit_early(game, "malloc error for map geometry row", EXIT_FAILURE);
// 		ft_memset(geometry[i], 32, map->horiz_blocks);	// filling up the whole string with spaces (' ' - ascii value 32)
// 		geometry[i][map->horiz_blocks] = 0;				// null termination at the end of each string
// 	}
// 	next_line = get_next_line(map->fd);
// 	if (!next_line)
// 		exit_early(game, "gnl", EXIT_FAILURE);
// 	i = -1;
// 	while (++i < map->vert_blocks)
// 	{
// 		j = -1;
// 		while (next_line && ++j < map->horiz_blocks)
// 		{
// 			if (is_valid_block(next_line[j]))
// 			{
// 				geometry[i][j] = next_line[j];
// 				if (is_player(next_line[j]))
// 				{
// 					map->pl_posx = j * BLOCK_SIZE;
// 					map->pl_posy = i * BLOCK_SIZE;
// 				}
// 			}
// 		}
// 		free(next_line);
// 		next_line = get_next_line(map->fd);
// 	}
// 	map->map_array = geometry;
// }

static void	initialize_map2D(t_game *game, t_map *map)
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
	parse_map(map, &geometry, next_line);
	map->map_array = geometry;
}

static void	parse_map(t_map *map, char ***geo, char *nxtline)
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
					map->pl_posx = j * BLOCK_SIZE;
					map->pl_posy = i * BLOCK_SIZE;
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
