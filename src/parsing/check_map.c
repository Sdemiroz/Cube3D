/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:25:26 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/07 17:53:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		check_map(t_game *game);
static int	player_counter_check(t_game *game);


bool	empty_line(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_isspace(line[x]) && line[x] != '\n')
			return (false);
		x++;
	}
	return (true);
}

void	assign_direction(t_map *map, char player_dir)
{
	t_data	*data;

	data = map->data;
	data->ini_dir = player_dir;
	if (player_dir == 'E')
		data->cur_dir = 0; // 0 degrees in radians
	else if (player_dir == 'N')
		data->cur_dir = PI / 2; // 90 degrees in radians
	else if (player_dir == 'W')
		data->cur_dir = PI; // 180 degrees in radians
	else if (player_dir == 'S')
		data->cur_dir = -PI / 2; // 270 or -90 degrees in radians
}

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
				game->data->pl_arr_x = x;
				game->data->pl_arr_y = y;
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count);
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
		exit_early(game,
			"Error: map must contain exactly 1 player start position\n", 1);
	game->data->pl_posx = game->data->pl_arr_x * game->data->tile_size;
	game->data->pl_posy = game->data->pl_arr_y * game->data->tile_size;
	dup_map = copy_map(game->map->map_array);
	if (!dup_map)
		exit_early(game, "Error: failed to duplicate map\n", 1);
	floodx = game->data->pl_posx / game->data->tile_size;
	floody = game->data->pl_posy / game->data->tile_size;
	valid = flood_fill(dup_map, floodx, floody);
	if (!valid)
		exit_early(game, "Error: map is not surrounded by walls\n", 1);
}
