/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:22:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/11 02:06:06 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_start(t_game *game)
{
	printf("Game started\n");
	draw_map(game);
	// if (mlx_image_to_window(game->mlx, game->img3D, 0, 0) < 0)
	// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
	// if (mlx_image_to_window(game->mlx, game->map->image, MAP_OFFSET_X, MAP_OFFSET_Y) < 0)
	// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
}
