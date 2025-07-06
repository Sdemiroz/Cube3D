/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/06 22:47:45 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game			*init_game(t_game *game, char *input);

static t_game	*set_game(t_game *game);
// static void		read_input(t_game *game, char *input);

t_game	*init_game(t_game *game, char *input)
{
	game = set_game(game);
	(void)input;
	// read_input(game, input);
	// parse_map(game, input);
	return (game);
}

static t_game	*set_game(t_game *game)
{
	game = get_game();
	if(!game)
		exit_early(game, "Malloc error Game\n", 1);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img_3d = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img_3d)
		exit_early(game, "game_img_3d: mlx_new_image", EXIT_FAILURE);
	
	game->map = get_map();
	if(!game->map)
		exit_early(game, "map: struct malloc", 1);
	// ft_bzero(game->map, sizeof(t_map));						// required?
	game->map->overview = mlx_new_image(game->mlx, MAP_H, MAP_W);
	if (!game->map->overview)
		exit_early(game, "map_overview: mlx_new_image", EXIT_FAILURE);

	game->player = get_player();
	if(!game->player)
		exit_early(game, "game_player: malloc\n", 1);
	// ft_bzero(game->player, sizeof(t_player));			// required?
	
	return (game);
}

// static void	read_input(t_game *game, char *input)
// {
// 	// int fd;

// 	(void)game;
// 	(void)input;

// }
