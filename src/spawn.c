/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:13:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/11 16:03:50 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*get_game(void);
t_map		*get_map(void);
t_player	*get_player(void);

t_game	*get_game(void)
{
	static t_game	*game = NULL;
	int				i;
	
	i = -1;
	if (!game)
	{
		game = ft_malloc(sizeof(t_game));
		if (game)
		{
			game->mlx = NULL;
			game->img3D = NULL;
			game->img3D_inst_id = -1;	// Initialize 3D image instance ID to -1
			while (++i < 4)
				game->walls[i] = NULL;	// Initialize wall textures to NULL
			game->map = NULL;			// Initialize map pointer to NULL
			game->player = NULL;		// Initialize player pointer to NULL
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
			// ft_bzero(map, sizeof(t_map));			// required?
			map->image = NULL;
			map->image_inst_id = -1;
			map->map_array = NULL;
			map->fd = -1;
			map->height = MAP_H;
			map->width = MAP_W;
			map->player = NULL;
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
			// ft_bzero(player, sizeof(t_player));		// required?
			player->blob2D = NULL;
			player->blob_inst_id = -1;
			player->blob_dia = PLAYER_DIA;
			player->pos_x = START_PX;
			player->pos_y = START_PY;
			player->dia2D = PLAYER_DIA;
			player->gun3D = NULL;
		}
	}
	return (player);
}
