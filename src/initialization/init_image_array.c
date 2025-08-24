/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:56:54 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/07 15:23:39 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	create_image_array(t_map *map, t_data *data);

static void	morph_map_to_img(char **map, char **img, int hop, t_data *data);
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
	morph_map_to_img(map->map_array, img_array, data->tile_size, data);
}

static void	morph_map_to_img(char **map, char **img, int hop, t_data *data)
{
	int		img_xy[2];		// Image coordinate iterators
	int		map_xy[2];		// Map coordinate iterators
	int		map_xy_max[2];	// Map coordinate limits
	char	c;
	
	// map-coordinate limits init
	map_xy_max[0] = data->tiles_x;
	map_xy_max[1] = data->tiles_y;

	map_xy[1] = -1;
	img_xy[1] = 0;
	while (++map_xy[1] < map_xy_max[1])
	{
		map_xy[0] = -1;
		img_xy[0] = 0;
		while (++map_xy[0] < map_xy_max[0])
		{
			c = map[map_xy[1]][map_xy[0]];
			if (is_player(c))
				c = '0';
			write_char_block(img, img_xy[0], img_xy[1], c);
			img_xy[0] += hop;
		}
		img_xy[1] += hop;
	}
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
