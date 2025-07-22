/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:00:15 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/22 20:53:26 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_minimap(t_game *game, t_map *map);

static void	write_to_map_array(t_map *map, char ***geo, char *nxtline);
static void	assign_direction(t_map *map, char player_dir);


void	parse_minimap(t_game *game, t_map *map)
{
	char	**geometry;
	char	*next_line;
	int		i;

	geometry = malloc(map->data->tiles_y * sizeof(char *) + 1);
	if (!geometry)
		exit_early(game, "malloc error for map geometry", EXIT_FAILURE);
	geometry[map->data->tiles_y] = NULL;
	i = -1;
	while (++i < map->data->tiles_y)
	{
		geometry[i] = malloc(map->data->tiles_x * sizeof(char) + 1);
		if (!geometry[i])
			exit_early(game, "malloc error for map geometry row", EXIT_FAILURE);
		ft_memset(geometry[i], 32, map->data->tiles_x);	// filling up the whole string with spaces (' ' - ascii value 32)
		geometry[i][map->data->tiles_x] = '\0';			// null termination at the end of each string
	}
	next_line = get_next_line(map->fd);
	if (!next_line)
		exit_early(game, "gnl", EXIT_FAILURE);
	write_to_map_array(map, &geometry, next_line);
	map->map_array = geometry;
}

static void	write_to_map_array(t_map *map, char ***geo, char *nxtline)
{
	int		i;
	int		j;
	char	**geometry;
	
	geometry = *geo;
	i = -1;
	while (++i < map->data->tiles_y)
	{
		j = -1;
		while (nxtline && ++j < map->data->tiles_x)
		{
			if (is_valid_block(nxtline[j]))
			{
				geometry[i][j] = nxtline[j];
				if (is_player(nxtline[j]))
				{
					map->pl_posx = j * TILE_SIZE;
					map->pl_posy = i * TILE_SIZE;
					assign_direction(map, nxtline[j]);
				}
			}
		}
		free(nxtline);
		nxtline = get_next_line(map->fd);
	}
}

static void	assign_direction(t_map *map, char player_dir)
{
	map->pl_ini_dir = player_dir;
	if (player_dir == 'E')
		map->pl_dir = 0;		// 0 degrees in radians
	else if (player_dir == 'N')
		map->pl_dir = PI / 2;	// 90 degrees in radians
	else if (player_dir == 'W')
		map->pl_dir = PI;		// 180 degrees in radians
	else if (player_dir == 'S')
		map->pl_dir = -PI / 2;	// 270 or -90 degrees in radians
}