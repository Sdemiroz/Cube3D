/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/13 02:06:48 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_early(t_game *game, char *msg, int ret)
{
	int	i;
	int	x;

	x = 0;
	if (msg)
		perror(msg);
	if (!game)
		exit(ret);
	// if (game->walls)
	// {
	// 	while (x < 4)
	// 	{
	// 		if (game->walls[x])
	// 			mlx_delete_texture(game->walls[x]);
	// 		x++;
	// 	}
	// }
	if (game->mlx)	// still experimental
	{
		if (game->map->image)
			mlx_delete_image(game->mlx, game->map->image);
		if (game->img3D)
			mlx_delete_image(game->mlx, game->img3D);
		mlx_close_window(game->mlx);	// close a window if it is open to free the resources, mlx instance stays allocated
		mlx_terminate(game->mlx);		// terminate the mlx instance by freeing the allocation
	}
	if (!(game->map->fd < 0))
		close(game->map->fd);
	if (game->map && game->map->map_array)
	{
		i = -1;
		while (game->map->map_array[++i])
			free(game->map->map_array[i]);
		free(game->map->map_array);
	}
	main_cleanup(ret);
}
