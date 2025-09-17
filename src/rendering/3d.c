/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:20:14 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/09/12 12:00:45 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_3d_walls(t_game *game);
void	erase_3d_walls(t_game *game);

static void	draw_column(t_game *game, int screen_x, int wall_height,
		float wall_hit_x, t_txr *texture);
static void	erase_column(t_game *game, int screen_x, int wall_height,
		float wall_hit_x, t_txr *texture);
static uint32_t	get_pixel_from_texture(t_txr *texture, int x, int y);

/*
Main rendering function that:
- Loops through each screen column (x = 0 to window width)
- Generates test data for wall height, texture coordinates, and texture selection
- Calls `draw_column()` for each column
*/
void	draw_3d_walls(t_game *game)
{
	int			screen_x;
	int			wall_height;
	float 		wall_hit_x;
	
	t_data		*data;
	int			tile_size;
	t_rays		**rays;
	t_rays		*ray;
	int			focal_length;
	int			colm_h;
	// int			wind_w;
	int			num_rays;

	if (!game || !game->img3D)
		exit_early(game, "render_3d_walls: Invalid game or img3D", EXIT_FAILURE);
	focal_length = 20;
	data = game->data;
	tile_size = data->tile_size;
	num_rays = data->num_rays;
	rays = game->player->rays;
	// wind_w = game->data->wind_w;
	colm_h = focal_length * game->data->wind_h;
	screen_x = 0;
	while (screen_x < num_rays)
	{
		ray = rays[screen_x];
		wall_height = (int)(colm_h / ray->wall_distance);
		// wall_hit_x = (screen_x % 100) / 100.0f;
		wall_hit_x = (ray->hit_x % tile_size) / ((float)tile_size);
		draw_column(game, screen_x, wall_height, wall_hit_x, ray->tex);
		screen_x++;
	}
}

void	erase_3d_walls(t_game *game)
{
	int			screen_x;
	int			wall_height;
	float 		wall_hit_x;
	
	t_data		*data;
	int			tile_size;
	t_rays		**rays;
	t_rays		*ray;
	int			focal_length;
	int			colm_h;
	// int			wind_w;
	int			num_rays;

	if (!game || !game->img3D)
		exit_early(game, "render_3d_walls: Invalid game or img3D", EXIT_FAILURE);

	focal_length = 20;
	data = game->data;
	tile_size = data->tile_size;
	num_rays = data->num_rays;
	rays = game->player->rays;
	// wind_w = game->data->wind_w;
	colm_h = focal_length * game->data->wind_h;
	screen_x = 0;
	while (screen_x < num_rays)
	{
		ray = rays[screen_x];
		wall_height = (int)(colm_h / ray->wall_distance);
		// wall_hit_x = (screen_x % 100) / 100.0f;
		wall_hit_x = (ray->hit_x % tile_size) / ((float)tile_size);
		erase_column(game, screen_x, wall_height, wall_hit_x, ray->tex);	// fill with transparent pixels to erase previously drawn pixels
		screen_x++;
	}
}

/*
`draw_column(game, screen_x, wall_height, wall_hit_x, texture)`
Renders a single vertical column with:
- `x`: Screen column position
- `wall_height`: Height of wall in pixels (affects distance/perspective)
- `wall_hit_x`: Texture X coordinate (0.0 to 1.0) where ray hit the wall
- `texture`: Which texture to use (NO_texture, SO_texture, WE_texture, EA_texture)
*/
static void	draw_column(t_game *game, int screen_x, int wall_height,
		float wall_hit_x, t_txr *texture)
{
	int		y;
	int		wall_start_y;
	int		wall_end_y;
	int		tex_x;
	int		tex_y;
	double	step;
	uint32_t	color;

	if (!texture || screen_x < 0 || screen_x >= game->data->wind_w)
		return;
	wall_start_y = (game->data->wind_h - wall_height) / 2;
	wall_end_y = wall_start_y + wall_height;
	if (wall_start_y < 0)
		wall_start_y = 0;
	if (wall_end_y >= game->data->wind_h)
		wall_end_y = game->data->wind_h - 1;
	tex_x = (int)(wall_hit_x * texture->width) % texture->width;
	step = (double)texture->height / wall_height;
	y = wall_start_y;
	while (y < wall_end_y)
	{
		tex_y = (int)((y - wall_start_y) * step);
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(game->img3D, screen_x, y, color);
		y++;
	}
}

static void	erase_column(t_game *game, int screen_x, int wall_height,
		float wall_hit_x, t_txr *texture)
{
	int		y;
	int		wall_start_y;
	int		wall_end_y;
	// int		tex_x;
	int		tex_y;
	double	step;
	uint32_t	color;

	if (!texture || screen_x < 0 || screen_x >= game->data->wind_w)
		return;
	(void)wall_hit_x;
	wall_start_y = (game->data->wind_h - wall_height) / 2;
	wall_end_y = wall_start_y + wall_height;
	if (wall_start_y < 0)
		wall_start_y = 0;
	if (wall_end_y >= game->data->wind_h)
		wall_end_y = game->data->wind_h - 1;
	// tex_x = (int)(wall_hit_x * texture->width) % texture->width;
	step = (double)texture->height / wall_height;
	y = wall_start_y;
	while (y < wall_end_y)
	{
		tex_y = (int)((y - wall_start_y) * step);
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		color = 0;
		mlx_put_pixel(game->img3D, screen_x, y, color);
		y++;
	}
}

/*
`get_pixel_from_texture(texture, x, y)`
Extracts RGBA color from texture at given coordinates with bounds checking.
*/
static uint32_t	get_pixel_from_texture(t_txr *texture, int x, int y)
{
	int		index;
	uint8_t	*pixels;

	if (!texture || x < 0 || y < 0 || x >= (int)texture->width || y >= (int)texture->height)
	{
		printf("Invalid texture access: tex=%p, x=%d, y=%d, size=%ux%u\n",
			texture, x, y, texture ? texture->width : 0, texture ? texture->height : 0);
		return (0xFF00FFFF);  // Pink color for invalid/missing texture
	}
	pixels = texture->pixels;
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return ((pixels[index] << 24) | (pixels[index + 1] << 16) |
			(pixels[index + 2] << 8) | pixels[index + 3]);
}
