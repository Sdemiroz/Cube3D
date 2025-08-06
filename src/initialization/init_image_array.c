/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:56:54 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/06 20:58:06 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	create_image_array(t_map *map, t_data *data);

static void	morph_map_to_img(t_map *map, t_data *data);
static void	write_char_block(char **image, int x, int y, char c);


void	create_image_array(t_map *map, t_data *data)
{
	char	**img_array;
	int		img_x;
	int		img_y;
	int		i;

	img_x = data->mmp_w;
	img_y = data->mmp_h;
	img_array = ft_malloc((img_y + 1) * sizeof(char *));
	if (!img_array)
		printf("img_array malloc had failed\n");
	i = -1;
	while (++i < img_y)
	{
		img_array[i] = ft_malloc((img_x + 1) * sizeof(char));
		if (!img_array[i])
			printf("img_array[%d] malloc had failed\n", i);
		img_array[i][img_x] = '\0'; // Null-terminate each row
	}
	img_array[i] = NULL; // Null-terminate the array of strings
	map->img_array = img_array;
	morph_map_to_img(map, data);
}

// // Function to fill a block of tile_size in the image_array with a provided char
// static void	place_char_block_in_img(char **img, int x, int y, char c)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < TILE_SIZE)
// 	{
// 		j = -1;
// 		while (++j < TILE_SIZE)
// 		{
// 			img[y * TILE_SIZE + i][x * TILE_SIZE + j] = c;
// 		}
// 	}
// }

// // Function to morph the map array into an image array by placing blocks of characters for each char found in the map using place_char_block_in_img
// static void	morph_map_to_img(t_map *map, int tiles[2])
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < tiles[1])
// 	{
// 		x = -1;
// 		while (++x < tiles[0])
// 		{
// 			place_char_block_in_img(map->img_array, x, y, map->map_array[y][x]);
// 		}
// 	}
// }

static void	morph_map_to_img(t_map *map, t_data *data)
{
	char	**img_array;
	char	**map_array;
	int		hop;
	
	int		x;
	int		y;
	
	int		i;
	int		j;
	int		tiles_x;
	int		tiles_y;

	char	c;

	img_array = map->img_array;
	map_array = map->map_array;
	hop = data->tile_size;
	
	// map-coordinates
	tiles_x = data->tiles_x;
	tiles_y = data->tiles_y;
	
	j = -1;
	y = 0;
	while (++j < tiles_y)
	{
		i = -1;
		x = 0;
		while (++i < tiles_x)
		{
			c = map_array[j][i];
			if (is_player(c))
				c = '0';
			write_char_block(img_array, x, y, c);
			x += hop;
		}
		y += hop;
	}
	printf("ALL IS WELL\n");
}

static void	write_char_block(char **img, int x, int y, char c)
{
	int		tile_size;
	int		cur_x;
	int		x_limit;
	int		y_limit;

	tile_size = get_data()->tile_size;
	x_limit = x + tile_size;
	y_limit = y + tile_size;
	while (y < y_limit)
	{
		cur_x = x;
		while (cur_x < x_limit)
		{
			img[y][cur_x] = c;
			cur_x++;
		}
		y++;
	}
}

// static void	write_char_block(char **img, int x, int y, char c)
// {
// 	int		tile_size;
// 	int		x_limit;
// 	int		y_limit;
// 	int		cur_x;
// 	int		cur_y;
// 	t_data	*data;

// 	data = get_data();
// 	tile_size = data->tile_size;
// 	y_limit = y + tile_size;
// 	cur_y = y;
// 	while (cur_y < y_limit && cur_y < data->mmp_h)
// 	{
// 		x_limit = x + tile_size;
// 		cur_x = x;
// 		while (cur_x < x_limit && cur_x < data->mmp_w)
// 		{
// 			img[cur_y][cur_x] = c;
// 			cur_x++;
// 		}
// 		cur_y++;
// 	}
// }
