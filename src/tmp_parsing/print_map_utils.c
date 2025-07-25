/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:44:00 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/23 13:44:42 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_array_printer(t_map *map, int flag);

static void	printf_map(t_map *map);
static void	printf_map_colorful(t_map *map);
static void	write_map_colorful(t_map *map);

/*
Function to print map array using an int-based flag
  - Turn the first bit on for write-based with color
  - Turn the second bit on for printf-based without color
  - Turn the third bit on for printf-based with color
Note: write-based is the least computationally-heavy, and why it was written
*/
void	map_array_printer(t_map *map, int flag)
{
	if (flag & 4)
		printf_map_colorful(map);	// print from parsed map
	if (flag & 2)
		printf_map(map);	// print from parsed map
	if (flag & 1)
		write_map_colorful(map);		// print from parsed map
}

static void	printf_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->data->tiles_y)
		printf("%s\n", map->map_array[i]);
}

static void	printf_map_colorful(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	printf("\033[0;34m"); // Blue for walls
	while (++i < map->data->tiles_y)
	{
		j = -1;
		while (++j < map->data->tiles_x)
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

static void	write_map_colorful(t_map *map)
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
