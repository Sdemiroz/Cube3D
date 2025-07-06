/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:13:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/06 19:23:27 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*get_game(void);
t_map		*get_map(void);
t_player	*get_player(void);

t_game	*get_game(void)
{
	static t_game	*game = NULL;
	
	if (!game)
	{
		game = ft_malloc(sizeof(t_game));
		if (game)
		{
			game->mlx = NULL;
			game->img_3d = NULL;
			game->walls[0] = NULL;
			game->walls[1] = NULL;
			game->walls[2] = NULL;
			game->walls[3] = NULL;
		}
	}
	return (game);
}

t_map	*get_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = ft_malloc(sizeof(t_map));
		if (map)
		{
			map->height = -1;
			map->width = -1;
			map->overview = NULL;
		}
	}
	return (map);
}

t_player	*get_player(void)
{
	static t_player	*player = NULL;

	if (!player)
	{
		player = ft_malloc(sizeof(t_player));
		if (player)
		{
			player->start_x = -1;
			player->start_y = -1;
		}
	}
	return (player);
}
