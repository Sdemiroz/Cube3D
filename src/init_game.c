/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/10 20:13:30 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game			*init_game(char *arg);

static void		set_game_elements(t_game *game, char *path_to_map);

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
	game->img_3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img_3d)
		exit_early(game, "game_img_3d: mlx_new_image", EXIT_FAILURE);
	
	game->map = get_map();
	if(!game->map)
		exit_early(game, "map: struct malloc", 1);

	game->map->overview = mlx_new_image(game->mlx, MAP_W, MAP_H);
	if (!game->map->overview)
		exit_early(game, "map_overview: mlx_new_image", EXIT_FAILURE);
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);

	game->player = get_player();
	if(!game->player)
		exit_early(game, "game_player: malloc\n", 1);
}
