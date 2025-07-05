/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/05 22:40:22 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*init_game(t_game *game, char *input);

static void	set_game(t_game *game);
static void	read_input(t_game *game, char *input);

t_game	*init_game(t_game *game, char *input)
{
	set_game(game);
	read_input(game, input);

	return (game);
}

static void	set_game(t_game *game)
{
	t_map		*map;
	t_player	*player;

	game = get_game();
	if(!game)
		ft_error2(game, "Malloc error Game\n", 1);

	map = get_map();
	if(!map)
		ft_error2(game, "Malloc error Map\n", 1);
	ft_bzero(map, sizeof(map));

	player = get_player();
	if(!player)
		ft_error2(game, "Malloc error Player\n", 1);
	ft_bzero(player, sizeof(player));
	
	game->map = map;
	game->player = player;
}

static void	read_input(t_game *game, char *input)
{
	// int fd;

	(void)game;
	(void)input;

}
