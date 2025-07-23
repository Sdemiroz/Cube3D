/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:17:28 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 05:57:47 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[x] || y >= (int)ft_strlen(map[x]))
		return (false);
	if (map[x][y] == ' ' || map[x][y] == '\0')
		return (false);
	if (map[x][y] == '1' || map[x][y] == 'X')
		return (true);
	map[x][y] = 'X';
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

	padded_line = ft_malloc(sizeof(char) * (game->map->width + 1));
	if (!padded_line)
		exit_early(game, "Error allocating padded line\n", 1);
	i = 0;
	while (i < game->map->height)
	{
		line_len = ft_strlen(game->map->map_array[i]);
		if (line_len < game->map->width)
		{
			ft_memset(padded_line, ' ', game->map->width);
			padded_line[game->map->width] = '\0';
			ft_memcpy(padded_line, game->map->map_array[i], line_len);
			game->map->map_array[i] = ft_malloc(sizeof(char) * (game->map->width + 1));
			if (!game->map->map_array[i])
				exit_early(game, "Error allocating padded line\n", 1);
			ft_strlcpy(game->map->map_array[i], padded_line, game->map->width + 1);
		}
		i++;
	}
}


int	check_key_data_completion(t_game *game)
{
	if (game->NO_texture && game->SO_texture && game->WE_texture
		&& game->EA_texture)
		{
			if(game->ceiling_color.r && game->floor_color.r)
				return (1);
		}
	return (0);
}
