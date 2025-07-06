/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/06 19:45:49 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_early(t_game *game, char *msg, int ret)
{
	int	x;

	x = 0;
	if (msg)
		perror(msg);
	if (!game)
		exit(ret);
	while (x != 5)	// why 5?
	{
		if (game->walls[x])
			mlx_delete_texture(game->walls[x]);
		x++;
	}
	if (game->mlx)	// still experimental
	{
		if (game->map->overview)
			mlx_delete_image(game->mlx, game->map->overview);
		if (game->img_3d)
			mlx_delete_image(game->mlx, game->img_3d);
		mlx_close_window(game->mlx);	// close a window if it is open to free the resources, mlx instance stays allocated
		mlx_terminate(game->mlx);		// terminate the mlx instance by freeing the allocation
	}
	main_cleanup(ret);
}
