/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:20:14 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/09/27 02:44:56 by sdemiroz         ###   ########.fr       */
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
	
	t_rays		**rays;
	t_rays		*ray;
	int			focal_length;
	int			colm_h;
	// int			wind_w;
	int			num_rays;

	if (!game || !game->img3D)
		exit_early(game, "render_3d_walls: Invalid game or img3D", EXIT_FAILURE);
	focal_length = 15;
	rays = game->player->rays;
	// wind_w = game->data->wind_w;
	colm_h = focal_length * game->data->wind_h;
	num_rays = game->data->num_rays;
	screen_x = 0;
	while (screen_x < num_rays)
	{
	ray = rays[screen_x];
	if (ray->inv_wall_distance <= 0.0)
	{
		screen_x++;
		continue ;
	}
	wall_height = (int)(colm_h * ray->inv_wall_distance);
	wall_hit_x = ray->tex_u;
	if (wall_hit_x < 0.0)
		wall_hit_x = 0.0;
	else if (wall_hit_x > 1.0)
		wall_hit_x = 1.0;
	draw_column(game, screen_x, wall_height, wall_hit_x, ray->tex);
		screen_x++;
	}
}

void	erase_3d_walls(t_game *game)
{
	int			screen_x;
	int			wall_height;
	float 		wall_hit_x;
	
	t_rays		**rays;
	t_rays		*ray;
	int			focal_length;
	int			colm_h;
	// int			wind_w;
	int			num_rays;

	if (!game || !game->img3D)
		exit_early(game, "render_3d_walls: Invalid game or img3D", EXIT_FAILURE);

	rays = game->player->rays;
	// wind_w = game->data->wind_w;
	focal_length = 15;
	colm_h = focal_length * game->data->wind_h;
	num_rays = game->data->num_rays;
	screen_x = 0;
	while (screen_x < num_rays)
	{
	ray = rays[screen_x];
	if (ray->inv_wall_distance <= 0.0)
	{
		screen_x++;
		continue ;
	}
	wall_height = (int)(colm_h * ray->inv_wall_distance);
	wall_hit_x = ray->tex_u;
	if (wall_hit_x < 0.0)
		wall_hit_x = 0.0;
	else if (wall_hit_x > 1.0)
		wall_hit_x = 1.0;
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
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
	uint32_t	color;
	double	wall_start;
	double	wall_end;
	int		window_h;

	window_h = game->data->wind_h;
	if (!texture || screen_x < 0 || screen_x >= game->data->wind_w
		|| wall_height <= 0)
		return;
	wall_start = ((double)window_h - (double)wall_height) / 2.0;
	wall_end = wall_start + wall_height;
	draw_start = (int)floor(wall_start);
	draw_end = (int)ceil(wall_end) - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= window_h)
		draw_end = window_h - 1;
	if (draw_end < draw_start)
		return;

	// High-precision texture sampling - avoid integer truncation
	double tex_x_precise = wall_hit_x * texture->width;
	tex_x = (int)tex_x_precise;
	if (tex_x >= (int)texture->width) tex_x = texture->width - 1;
	if (tex_x < 0) tex_x = 0;

	tex_step = (double)texture->height / (double)wall_height;
	tex_pos = ((double)draw_start - wall_start) * tex_step;
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(game->img3D, screen_x, y, color);
		y++;
		tex_pos += tex_step;
	}
}

static void	erase_column(t_game *game, int screen_x, int wall_height,
		float wall_hit_x, t_txr *texture)
{
	int		y;
	int		draw_start;
	int		draw_end;
	uint32_t	color;
	double	wall_start;
	double	wall_end;
	int		window_h;

	window_h = game->data->wind_h;
	if (!texture || screen_x < 0 || screen_x >= game->data->wind_w
		|| wall_height <= 0)
		return;
	(void)wall_hit_x;
	wall_start = ((double)window_h - (double)wall_height) / 2.0;
	wall_end = wall_start + wall_height;
	draw_start = (int)floor(wall_start);
	draw_end = (int)ceil(wall_end) - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= window_h)
		draw_end = window_h - 1;
	if (draw_end < draw_start)
		return;
	y = draw_start;
	while (y <= draw_end)
	{
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
		// printf("Invalid texture access: tex=%p, x=%d, y=%d, size=%ux%u\n",
		// 	texture, x, y, texture ? texture->width : 0, texture ? texture->height : 0);
		return (0xFF00FFFF);  // Pink color for invalid/missing texture
	}
	pixels = texture->pixels;
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	return ((pixels[index] << 24) | (pixels[index + 1] << 16) |
			(pixels[index + 2] << 8) | pixels[index + 3]);
}
