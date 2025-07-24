/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:13:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/24 21:08:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game		*get_game(void);
t_data		*get_data(void);
t_map		*get_map(void);
t_player	*get_player(void);
t_rays		*get_rays(void);

static void	initialize_map_data(t_data *data);


t_game	*get_game(void)
{
	static t_game	*game = NULL;
	int				i;
	
	i = -1;
	if (!game)
	{
		game = ft_malloc(sizeof(t_game));
		if (game)
		{
			game->data = NULL;
			game->mlx = NULL;
			game->img3D = NULL;
			game->img3D_inst_id = -1;	// Initialize 3D image instance ID to -1
			// game->gun3D = NULL;
			// game->gun_inst_id = -1;
			// while (++i < 4)
			// 	game->walls[i] = NULL;	// Initialize wall textures to NULL
			game->map = NULL;			// Initialize map pointer to NULL
			game->player = NULL;		// Initialize player pointer to NULL
			game->rays = NULL;
		}
	}
	return (game);
}

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
			data->fov = FOV;
			data->num_rays = NUM_RAYS;
			data->ini_dir = 'N';
			data->prev_dir = PI / 2;
			data->cur_dir = PI / 2;
			data->cosine = cos(data->cur_dir);
			data->sine = sin(data->cur_dir);
			initialize_map_data(data);
		}	
	}
	return (data);
}

static void	initialize_map_data(t_data *data)
{
	data->mmp_w = MAP_W;
	data->mmp_h = MAP_H;
	data->mmp_offx = MAP_OFFSET_X;
	data->mmp_offy = MAP_OFFSET_Y;
	data->mmp_scale = MAP_SCALE;
	data->tile_size = TILE_SIZE;
	data->tiles_x = MAP_W / TILE_SIZE;
	data->tiles_y = MAP_H / TILE_SIZE;
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
			map->game = NULL;
			map->player = NULL;
			map->rays = NULL;
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
			player->game = NULL;
			player->map = NULL;
			player->rays = NULL;
		}
	}
	return (player);
}

t_rays	*get_rays(void)
{
	static t_rays	*rays = NULL;
	
	if (!rays)
	{
		rays = ft_malloc(sizeof(t_rays));
		if (rays)
		{
			rays->data = NULL;
			rays->rays = NULL;
			rays->rays_inst_id = -1;
			rays->game = NULL;
			rays->map = NULL;
			rays->player = NULL;
		}
	}
	return (rays);
}
