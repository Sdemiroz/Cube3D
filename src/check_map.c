/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:25:26 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/25 19:44:28 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		check_map(t_game *game);
static int	player_counter_check(t_game *game);

static int	player_counter_check(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	x = 0;
	player_count = 0;
	while (game->map->map_array[x])
	{
		y = 0;
		while (game->map->map_array[x][y])
		{
			if (game->map->map_array[x][y] == 'N'
				|| game->map->map_array[x][y] == 'E'
				|| game->map->map_array[x][y] == 'S'
				|| game->map->map_array[x][y] == 'W')
			{
				game->data->pl_posx = x;
				game->data->pl_posy = y;
				player_count++;
			}
			y++;
		}
		x++;
	}
	return(player_count);
}

void	check_map(t_game *game)
{
	int		x;
	char	**dup_map;
	bool	valid;

	x = player_counter_check(game);
	if (x != 1)
		exit_early(game, "Error: map must contain exactly 1 player start position\n", 1);
	dup_map = copy_map(game->map->map_array);
	if (!dup_map)
		exit_early(game, "Error: failed to duplicate map\n", 1);
	valid = flood_fill(dup_map,
		game->data->pl_posx,
		game->data->pl_posy);
	if (!valid)
		exit_early(game, "Error: map is not surrounded by walls\n", 1);
}
