/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/06/18 06:21:31 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_input(t_game *game, char *input)
{
	int fd;


}

t_game	*set_game(t_game *game)
{
	t_map		*map;
	t_player	*player;

	game = ft_malloc(sizeof(t_game));
	if(!game)
		ft_error(game, "Malloc error Game\n", 1);
	game->mlx = NULL;
	game->main_img = NULL;
	game->map_img = NULL;
	game->walls[0] = NULL;
	game->walls[1] = NULL;
	game->walls[2] = NULL;
	game->walls[3] = NULL;
	map = ft_malloc(sizeof(t_map));
	if(!map)
		ft_error(game, "Malloc error Map\n", 1);
	ft_bzero(map, sizeof(map));
	player = ft_malloc(sizeof(t_player));
	if(!player)
		ft_error(game, "Malloc error Player\n", 1);
	ft_bzero(player, sizeof(player));
	game->map = map;
	game->player = player;
	return(game);
}

t_game	*init_game(t_game *game, char *input)
{
	set_game(game);
	read_input(game, input);
}
