/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/06 17:30:34 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_early(t_game *game, char *msg, int ret);

static void	clear_map(t_game *game, t_map *map);
static void	clear_player(t_game *game, t_player *pl);
static void	clear_mlx(t_game *game);


void	exit_early(t_game *game, char *msg, int ret)
{
	if (msg)
		perror(msg);
	if (!game)
		exit(ret);

	if (game->mlx && game->map)
		clear_map(game, game->map);
	if (game->mlx && game->player)
		clear_player(game, game->player);
	if (game->mlx)
		clear_mlx(game);

	main_cleanup(ret);
}

static void	clear_map(t_game *game, t_map *map)
{
	// int	i;
	
	if (map->image)
		mlx_delete_image(game->mlx, map->image);
	if (!(map->fd < 0))
		close(map->fd);
	// if (map && map->map_array)
	// {
	// 	i = -1;
	// 	while (map->map_array[++i])
	// 		free(map->map_array[i]);
	// 	free(map->map_array);
	// }
}

static void	clear_player(t_game *game, t_player *pl)
{
	if (pl->blob2D)
		mlx_delete_image(game->mlx, pl->blob2D);
	if (pl->view)
		mlx_delete_image(game->mlx, pl->view);
	// if (pl->gun3D)
	// 	mlx_delete_image(game->mlx, pl->gun3D);	// to be used if an overlay of gun image is separately spawned and used
}

static void	clear_mlx(t_game *game)
{
	// int	x;
	
	// x = 0;
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
		if (game->img3D)
			mlx_delete_image(game->mlx, game->img3D);
		mlx_close_window(game->mlx);	// close a window if it is open to free the resources, mlx instance stays allocated
		mlx_terminate(game->mlx);		// terminate the mlx instance by freeing the allocation
	}
}
