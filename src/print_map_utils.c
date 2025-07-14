/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:44:00 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/14 00:55:48 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(t_map *map);
void	print_map_colorful(t_map *map);
void	write_map_colorful(t_map *map);

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->vert_blocks)
		printf("%s\n", map->map_array[i]);
}

void	print_map_colorful(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	printf("\033[0;34m"); // Blue for walls
	while (++i < map->vert_blocks)
	{
		j = -1;
		while (++j < map->horiz_blocks)
		{
			if (map->map_array[i][j] == '1')
				printf("0");
				// printf("%c", map->map_array[i][j]);
			else if (is_player(map->map_array[i][j]))
			{
				printf("\033[0;31m"); // Red for player directions
				printf("%c", map->map_array[i][j]); // Red for player directions
				printf("\033[0;34m"); // Reset to blue for walls
			}
			else
				printf("%c", map->map_array[i][j]);	// Printing empty spaces
		}
		printf("\n"); // New line after each row
	}
	printf("\033[0m"); // Reset color
}

void	write_map_colorful(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	write(1, "\033[0;34m", 7); // Blue for walls
	while (map->map_array[++i])
	{
		j = -1;
		while (map->map_array[i][++j])
		{
			if (map->map_array[i][j] == '1')
				write(1, "I", 1);
				// printf("%c", map->map_array[i][j]);
			else if (is_player(map->map_array[i][j]))
			{
				write(1, "\033[0;31m", 7); // Red for player directions
				write(1, &map->map_array[i][j], 1); // Red for player directions
				write(1, "\033[0;34m", 7); // Reset to blue for walls
			}
			else
				write(1, &map->map_array[i][j], 1);	// Printing empty spaces
		}
		write(1, "\n", 1); // New line after each row
	}
	write(1, "\033[0m", 4); // Reset color
}
