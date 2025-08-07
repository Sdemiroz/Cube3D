/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:13:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/07 14:02:50 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_game		*get_game(void);
t_data		*get_data(void);
t_map		*get_map(void);
t_player	*get_player(void);
t_rays		**get_rays(void);

static void	initialize_map_data(t_data *data);


// t_game	*get_game(void)
// {
// 	static t_game	*game = NULL;

// 	if (!game)
// 	{
// 		game = ft_malloc(sizeof(t_game));
// 		if (game)
// 		{
// 			game->data = NULL;
// 			game->mlx = NULL;
// 			game->img3D = NULL;
// 			game->img3D_inst_id = -1;	// Initialize 3D image instance ID to -1
// 			// game->gun3D = NULL;
// 			// game->gun_inst_id = -1;

// 			game->map = NULL;			// Initialize map pointer to NULL
// 			game->player = NULL;		// Initialize player pointer to NULL
// 		}
// 	}
// 	return (game);
// }

t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = ft_malloc(sizeof(t_data));
		if (data)
		{
			data->wind_w = WIDTH;
			data->wind_h = HEIGHT;
			data->pl_dia = PLAYER_DIA;
			data->pl_posx = START_PX;
			data->pl_posy = START_PY;
			data->pl_center_x = START_PX + TILE_SIZE / 2;
			data->pl_center_y = START_PY + TILE_SIZE / 2;
			data->fov = FOV;
			data->num_rays = NUM_RAYS;
			data->ini_dir = 'N';
			data->prev_dir = PI / 2;
			data->cur_dir = PI / 2;
			data->cosine = cos(PI / 2);
			data->sine = sin(PI / 2);
			initialize_map_data(data);
		}
	}
	return (data);
}

static void	initialize_map_data(t_data *data)
{
	data->mmp_w = 0;
	data->mmp_h = 0;
	data->mmp_offx = MAP_OFFSET_X;
	data->mmp_offy = MAP_OFFSET_Y;
	data->mmp_scale = MAP_SCALE;
	data->tile_size = TILE_SIZE;
	data->tiles_x = 0;
	data->tiles_y = 0;
	data->fov_toggle = true;
}

t_map	*get_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = ft_malloc(sizeof(t_map));
		if (map)
		{
			map->data = NULL;
			map->image = NULL;
			map->image_inst_id = -1;
			map->fd = -1;
			map->map_array = NULL;
			map->img_array = NULL;
			map->game = NULL;
			map->player = NULL;
		}
	}
	return (map);
}

t_player	*get_player(void)
{
	static t_player	*player = NULL;

	if (!player)
	{
		player = ft_malloc(sizeof(t_player));
		if (player)
		{
			player->data = NULL;
			player->blob2D = NULL;
			player->blob_inst_id = -1;
			player->view = NULL;
			player->view_inst_id = -1;
			player->game = NULL;
			player->map = NULL;
			player->rays = NULL;
		}
	}
	return (player);
}

/*
Function that returns a pointer to an array of rays.
  - Used to get the rays for raycasting in the game.
  - Rays are initialized only once and reused throughout the game.
  - The rays are stored in a static array, which is allocated on the first call.
  - Returns a pointer to the array of rays.
  - Each ray is initialized with its index and other default values.

**Note:	Should only be called once the game and data structures are initialized
		as it uses the get_data() to get data for its allocation.
*/
t_rays	**get_rays(void)
{
	static t_rays	**rays = NULL;
	int				i;
	int				num_rays;

	if (!rays)
	{
		num_rays = get_data()->num_rays;
		rays = ft_malloc((num_rays + 1) * sizeof(t_rays *));
		if (rays)
		{
			i = -1;
			while (++i < num_rays)
			{
				rays[i] = ft_malloc(sizeof(t_rays));
				if (rays[i])
				{
					*rays[i] = (t_rays){
						.index = i,
					};
				}
			}
		}
		rays[num_rays] = NULL;		// Null-terminate the array of rays
	}
	return (rays);
}
