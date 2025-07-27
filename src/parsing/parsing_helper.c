/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:17:28 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/27 21:22:55 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		check_key_data_completion(t_game *game);
void	pad_shorter_lines(t_game *game);
char	**copy_map(char **original);
bool	flood_fill(char **map, int x, int y);
void	allocate_map_array(t_game *game, char *line);


void	allocate_map_array(t_game *game, char *line)
{
	if (!game->map->map_array)
		game->map->map_array = malloc(2 * sizeof(char *));
	else
		game->map->map_array = ft_recalloc(game->map->map_array,
				(game->data->tiles_y + 2) * sizeof(char *),
				(game->data->tiles_y + 1) * sizeof(char *));
	if (!game->map->map_array)
	{
		free(line);
		exit_early(game, "Error: Allocating map", 1);
	}
	game->map->map_array[game->data->tiles_y + 1] = NULL;
}

bool	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (false);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (true);
	map[y][x] = 'X';
	return (
		flood_fill(map, x + 1, y) &&
		flood_fill(map, x - 1, y) &&
		flood_fill(map, x, y + 1) &&
		flood_fill(map, x, y - 1)
	);
}

char	**copy_map(char **original)
{
	int		height;
	char	**copy;
	int		i;

	height = 0;
	while (original[height])
		height++;
	copy = (char **)ft_malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
			return (NULL);
		gc_add_local(copy[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}


void	pad_shorter_lines(t_game *game)
{
	int		i;
	char	*padded_line;
	int		line_len;

	padded_line = ft_malloc(sizeof(char) * (game->data->tiles_x + 1));
	if (!padded_line)
		exit_early(game, "Error allocating padded line\n", 1);
	i = 0;
	while (i < game->data->tiles_y)
	{
		line_len = ft_strlen(game->map->map_array[i]);
		if (line_len < game->data->tiles_x)
		{
			ft_memset(padded_line, ' ', game->data->tiles_x);
			padded_line[game->data->tiles_x] = '\0';
			ft_memcpy(padded_line, game->map->map_array[i], line_len);
			game->map->map_array[i] = ft_malloc(sizeof(char) * (game->data->tiles_x + 1));
			if (!game->map->map_array[i])
				exit_early(game, "Error allocating padded line\n", 1);
			ft_strlcpy(game->map->map_array[i], padded_line, game->data->tiles_x + 1);
		}
		i++;
	}
}


int	check_key_data_completion(t_game *game)
{
	// if (game->NO_texture)
	// 	printf("NO = 1\n");
	// if (game->SO_texture)
	// 	printf("SO = 1\n");
	// if (game->EA_texture)
	// 	printf("EA = 1\n");
	// if (game->WE_texture)
	// 	printf("WE = 1\n");
	// if (game->ceiling_color.r)
	// 	printf("CR = 1\n");
	// if (game->floor_color.r)
	// 	printf("FR = 1\n");
	
	// if (game->NO_texture && game->SO_texture && game->WE_texture
	// 		&& game->EA_texture && game->ceiling_color.r && game->floor_color.r)
	if (game->ceiling_color.r && game->floor_color.r)
		return (1);
	return (0);
}
