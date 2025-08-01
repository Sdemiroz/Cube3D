/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/01 03:42:41 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_game_elements(t_game *game, char *arg);

static void	init_game(t_game *game);

static void	init_minimap(t_game *game, char *path_to_map);
static void	init_player(t_game *game);
static void	init_rays(t_player *player, t_rays **rays);
static void	init_deltas(t_rays *ray, int num_rays, int i);
static void	init_angles(t_rays *ray, double cur_dir);
static void update_game_data_after_parsing(t_data *data);


void	init_game_elements(t_game *game, char *arg)
{
	init_game(game);

	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc failed", EXIT_FAILURE);
	game->player = get_player();
	if (!game->player)
		exit_early(game, "player malloc failed", EXIT_FAILURE);

	init_minimap(game, arg);
	init_player(game);
}

static void	init_game(t_game *game)
{
	t_data	*data;

	*game = (t_game){
		// .background_inst_id = -1,
		.img3D_inst_id = -1,
		// .gun_inst_id = -1,
	};

	data = get_data();
	if (!data)
		exit_early(game, "Scales malloc failed", EXIT_FAILURE);
	game->data = data;

	game->mlx = mlx_init(data->wind_w, data->wind_h, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);

	// game->background = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	// if (!game->background)
	// 	exit_early(game, "background_img: mlx_new_image", EXIT_FAILURE);

	game->img3D = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);
}

// static void	init_minimap(t_game *game, char *path_to_map)
// {
// 	t_data	*data;
// 	t_map	*map;

// 	data = game->data;
// 	map = game->map;

// 	map->data = data;

// 	map->fd = open(path_to_map, O_RDONLY);
// 	if(map->fd < 0)
// 		exit_early(game, "Error opening file", 1);
// 	map->image = mlx_new_image(game->mlx, data->mmp_w * data->tile_size, data->mmp_h * data->tile_size);
// 	if (!map->image)
// 		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);

// 	parse_minimap(map);
// 	map_array_printer(map, 1);	// extra utility, to be removed later

// 	map->game = game;
// 	map->player = game->player;
// 	map->rays = game->rays;
// }

static void	init_minimap(t_game *game, char *path_to_map)
{
	t_data	*data;
	t_map	*map;

	data = game->data;
	map = game->map;
	map->data = data;

	test_print_data();			// !! extra utility, to be removed later
	parse_game_data(game, path_to_map);
	update_game_data_after_parsing(data);

	// Initialize background after parsing (when colors are available)
	// init_background(game);

	test_print_data();			// !! extra utility, to be removed later
	map->image = mlx_new_image(game->mlx, data->mmp_w * data->tile_size, data->mmp_h * data->tile_size);
	if (!map->image)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);

	map_array_printer(map, 1);	// !! extra utility, to be removed later

	map->game = game;
	map->player = game->player;
}

static void	init_player(t_game *game)
{
	t_data		*data;
	t_player	*pl;

	data = game->data;
	pl = game->player;


	pl->data = data;
	pl->blob2D = mlx_new_image(game->mlx, data->tile_size, data->tile_size);
	if (!pl->blob2D)
		exit_early(game, "blob_img: mlx_new_image failed", EXIT_FAILURE);
	pl->view = mlx_new_image(game->mlx, data->mmp_w, data->mmp_h);
	if (!pl->view)
		exit_early(game, "view_img: mlx_new_image failed", EXIT_FAILURE);

	pl->rays = get_rays();
	if (!pl->rays)
		exit_early(game, "rays malloc failed", EXIT_FAILURE);
	init_rays(pl, pl->rays);

	pl->game = game;
	pl->map = game->map;
}

static void	init_rays(t_player *pl, t_rays **rays)
{
	t_data		*data;
	int			i;
	int			num_rays;
	double		cur_dir;
	t_rays		*ray;

	data = get_data();
	num_rays = data->num_rays;
	cur_dir = data->cur_dir;
	i = -1;
	while (++i < num_rays)
	{
		ray = rays[i];
		init_deltas(ray, num_rays, i);	// Left rays -> -ve, Right rays -> +ve
		init_angles(ray, data->cur_dir);
		ray->cosine = cos(ray->angle);
		ray->sine = sin(ray->angle);
		ray->length = 5 * data->tile_size;	// Preliminary initialising value
		ray->hit_x = -1;
		ray->hit_y = -1;
	}
	test_print_rays('d');	// !! extra utility, to be removed later
}

static void	init_deltas(t_rays *ray, int num_rays, int i)
{
	if (num_rays % 2 == 0)
	{
		if (i < num_rays / 2)
			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
		else
			ray->delta = ((double)(i + 1 - (num_rays / 2))) * PI / 180;
	}
	else
	{
		if (i < num_rays / 2)
			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
		else if (i == num_rays / 2)
			ray->delta = 0;
		else if (i > num_rays / 2)
			ray->delta = ((double)(i - (num_rays / 2))) * PI / 180;
	}
}

static void	init_angles(t_rays *ray, double cur_dir)
{
	double pi2 = 2 * PI;

	if (ray->delta < 0)
		ray->angle = fmod(cur_dir - ray->delta, pi2);
	else if (ray->delta == 0)
		ray->angle = cur_dir;
	else
		ray->angle = fmod(cur_dir + 2 * PI - ray->delta, pi2);
}

static void update_game_data_after_parsing(t_data *data)
{
	data->cosine = cos(data->cur_dir);
	data->sine = sin(data->cur_dir);
	data->mmp_w = data->tiles_x * data->tile_size;
	data->mmp_h = data->tiles_y * data->tile_size;
}

/*
 * BACKGROUND IMPLEMENTATION GUIDE - Implementation by GitHub Copilot
 *
 * This function creates a background image that fills the entire window
 * with ceiling color on the top half and floor color on the bottom half.
 *
 * HOW IT WORKS:
 * 1. Get window dimensions from game->data (wind_w x wind_h)
 * 2. Extract RGB colors from game->ceiling_color and game->floor_color
 * 3. Convert RGB to RGBA format (MLX42 uses RGBA with alpha channel)
 * 4. Use nested loops to fill each pixel:
 *    - Top half (y < height/2): ceiling color
 *    - Bottom half (y >= height/2): floor color
 * 5. Use mlx_put_pixel() to set each pixel color
 *
 * COLOR FORMAT: RGBA = (R << 24) | (G << 16) | (B << 8) | 0xFF
 * WHERE: R, G, B are 0-255, and 0xFF is full opacity
 */
/*
void	init_background(t_game *game)
{
	int		x, y;
	int		width, height;
	uint32_t	ceiling_rgba, floor_rgba;

	width = game->data->wind_w;
	height = game->data->wind_h;

	// Debug: Print the parsed colors
	printf("Ceiling color: R=%u, G=%u, B=%u\n",
		game->ceiling_color.r, game->ceiling_color.g, game->ceiling_color.b);
	printf("Floor color: R=%u, G=%u, B=%u\n",
		game->floor_color.r, game->floor_color.g, game->floor_color.b);

	// Convert RGB values to RGBA format (adding alpha channel with full opacity)
	ceiling_rgba = (game->ceiling_color.r << 24) | (game->ceiling_color.g << 16) |
	               (game->ceiling_color.b << 8) | 0xFF;
	floor_rgba = (game->floor_color.r << 24) | (game->floor_color.g << 16) |
	             (game->floor_color.b << 8) | 0xFF;

	printf("Ceiling RGBA: 0x%08X\n", ceiling_rgba);
	printf("Floor RGBA: 0x%08X\n", floor_rgba);

	// Fill the background image
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (y < height / 2)  // Top half - ceiling
				mlx_put_pixel(game->background, x, y, ceiling_rgba);
			else  // Bottom half - floor
				mlx_put_pixel(game->background, x, y, floor_rgba);
		}
	}

	printf("Background image initialized with %dx%d resolution\n", width, height);
}
*/
