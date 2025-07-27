/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:25:26 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/27 21:35:13 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		check_map(t_game *game);
static int	player_counter_check(t_game *game);

static int	player_counter_check(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (game->map->map_array[y])
	{
		x = 0;
		while (game->map->map_array[y][x])
		{
			if (game->map->map_array[y][x] == 'N'
				|| game->map->map_array[y][x] == 'E'
				|| game->map->map_array[y][x] == 'S'
				|| game->map->map_array[y][x] == 'W')
			{
				// game->data->pl_posx = x;
				// game->data->pl_posy = y;
				game->data->pl_posx = x * game->data->tile_size;
				game->data->pl_posy = y * game->data->tile_size;
				player_count++;
				printf("x = %d\n", game->data->pl_posx);
				printf("y = %d\n", game->data->pl_posy);
			}
			x++;
		}
		y++;
	}
	return(player_count);
}

void	check_map(t_game *game)
{
	int		x;
	char	**dup_map;
	bool	valid;
	int		floodx;
	int		floody;

	x = player_counter_check(game);
	if (x != 1)
		exit_early(game, "Error: map must contain exactly 1 player start position\n", 1);
	dup_map = copy_map(game->map->map_array);
	if (!dup_map)
		exit_early(game, "Error: failed to duplicate map\n", 1);
	floodx = game->data->pl_posx / game->data->tile_size;
	floody = game->data->pl_posy / game->data->tile_size;
	valid = flood_fill(dup_map, floodx, floody);
	if (!valid)
		exit_early(game, "Error: map is not surrounded by walls\n", 1);
	printf("here here here\n");
}
