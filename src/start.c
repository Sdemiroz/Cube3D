/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:22:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/09 22:07:28 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_start(t_game *game, char *path_to_map)
{
	printf("Game started\n");
	render_overview(game, path_to_map);
	if (mlx_image_to_window(game->mlx, game->map->overview, MAP_OFFSET_X, MAP_OFFSET_Y) < 0)
		exit_early(game, "Image to window failed", EXIT_FAILURE);
}
