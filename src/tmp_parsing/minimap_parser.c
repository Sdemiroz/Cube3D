/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:00:15 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/23 20:41:20 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_minimap(t_map *map);

static void	write_to_map_array(t_map *map, char ***geo, char *nxtline);
static void	assign_direction(t_map *map, char player_dir);


void	parse_minimap(t_map *map)
{
	char	**geometry;
	char	*next_line;
	int		i;

	geometry = ft_malloc(map->data->tiles_y * sizeof(char *) + 1);
	if (!geometry)
		exit_early(map->game, "Map geometry malloc", EXIT_FAILURE);
	geometry[map->data->tiles_y] = NULL;
	i = -1;
	while (++i < map->data->tiles_y)
	{
		geometry[i] = ft_malloc(map->data->tiles_x * sizeof(char) + 1);
		if (!geometry[i])
			exit_early(map->game, "Geometry row malloc failed", EXIT_FAILURE);
		ft_memset(geometry[i], 32, map->data->tiles_x);	// filling up the whole string with spaces (' ' - ascii value 32)
		geometry[i][map->data->tiles_x] = '\0';			// null termination at the end of each string
	}
	next_line = get_next_line(map->fd);
	if (!next_line)
		exit_early(map->game, "gnl", EXIT_FAILURE);
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
					map->data->pl_posx = j * map->data->tile_size;
					map->data->pl_posy = i * map->data->tile_size;
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
	t_data	*data;
	
	data = map->data;
	data->ini_dir = player_dir;
	if (player_dir == 'E')
		data->cur_dir = 0;		// 0 degrees in radians
	else if (player_dir == 'N')
		data->cur_dir = PI / 2;	// 90 degrees in radians
	else if (player_dir == 'W')
		data->cur_dir = PI;		// 180 degrees in radians
	else if (player_dir == 'S')
		data->cur_dir = -PI / 2;	// 270 or -90 degrees in radians
}