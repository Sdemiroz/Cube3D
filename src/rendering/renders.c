/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/04 03:51:50 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		init_graphics_rendering(void *param);

static void render_background(t_game *game);
static void render_3dview(t_game *game);
static void render_minimap(t_game *game, t_map *map);
static void	render_player_blob(t_game *game, t_player *pl);
static void render_player_2dview(t_game *game, t_player *pl);

void	init_graphics_rendering(void *param)
{
	t_game		*game;
	t_map		*map;
	t_player	*pl;
	t_rays		*rays;

	game = (t_game *)param;
	map = game->map;
	pl = game->player;

	render_background(game);
	render_3dview(game);
	render_minimap(game, map);
	render_player_blob(game, pl);
	render_player_2dview(game, pl);
}
static void render_background(t_game *game)
{
	if (game->background_inst_id == -1)
	{
		game->background_inst_id = mlx_image_to_window(game->mlx, game->background,
				0, 0);
		if (game->background_inst_id < 0)
			exit_early(game, "background_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void render_3dview(t_game *game)
{
	if (game->img3D_inst_id == -1)
	{
		game->img3D_inst_id = mlx_image_to_window(game->mlx, game->img3D,
				0, 0);
		if (game->img3D_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}

	// TODO: Call the 3D wall rendering function to draw textured walls
	render_3d_walls(game);
}

static void render_minimap(t_game *game, t_map *map)
{
	t_data	*data;

	data = game->data;

	if (map->image_inst_id == -1)
	{
		map->image_inst_id = mlx_image_to_window(game->mlx, map->image,
			data->mmp_offx, data->mmp_offy);
		if (map->image_inst_id < 0)
			exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
	}
}

static void	render_player_blob(t_game *game, t_player *pl)
{
	t_data	*data;

	data = game->data;
	if (pl->blob_inst_id == -1)
	{
		pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob2D,
				data->pl_posx + data->mmp_offx, data->pl_posy + data->mmp_offy);
		if (pl->blob_inst_id < 0)
			exit_early(game, "blob2D: mlx_image_to_window", EXIT_FAILURE);
	}
	else
	{
		pl->blob2D->instances[pl->blob_inst_id].x = data->pl_posx +
				data->mmp_offx;
		pl->blob2D->instances[pl->blob_inst_id].y = data->pl_posy +
				data->mmp_offy;
	}
}

static void render_player_2dview(t_game *game, t_player *pl)
{
	t_data	*data;

	data = game->data;

	if (pl->view_inst_id == -1)
	{
		printf("here it is\n");

		pl->view_inst_id = mlx_image_to_window(game->mlx, pl->view,
			data->mmp_offx, data->mmp_offy);
		if (pl->view_inst_id < 0)
			exit_early(game, "2Dview_img: mlx_image_to_window", EXIT_FAILURE);
	}
}

/*
 * ============================================================================
 * 3D WALL RENDERING WITH TEXTURES - Implementation Guide
 * ============================================================================
 *
 * This implementation creates a 3D view by drawing textured vertical strips
 * for each ray. Currently uses STATIC DATA for testing, but designed to be
 * easily adapted when real ray data becomes available.
 *
 * KEY CONCEPTS:
 * - Each screen column (x) represents one ray
 * - Wall height depends on distance (closer = taller)
 * - Texture sampling based on where ray hits the wall
 * - Different textures for different wall directions (NO/SO/WE/EA)
 * ============================================================================

// TODO: Step 1 - Implement get_pixel_from_texture()
// Helper function to safely get a pixel from a texture
/*
uint32_t	get_pixel_from_texture(mlx_texture_t *texture, int x, int y)
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

	// Convert RGBA bytes to uint32_t (MLX42 format)
	return ((pixels[index] << 24) | (pixels[index + 1] << 16) |
			(pixels[index + 2] << 8) | pixels[index + 3]);
}
*/

// TODO: Step 2 - Implement get_wall_texture()
// Choose which texture to use based on wall direction (static for now)
/*
static mlx_texture_t	*get_wall_texture(t_game *game, int ray_index)
{
	// STATIC TEST DATA: Cycle through different wall types
	// TODO: Replace with actual wall direction from ray data
	int wall_type = ray_index % 4;

	switch (wall_type)
	{
		case 0: return (game->NO_texture);  // North wall
		case 1: return (game->SO_texture);  // South wall
		case 2: return (game->WE_texture);  // West wall
		case 3: return (game->EA_texture);  // East wall
		default: return (game->NO_texture);
	}
}
*/

// TODO: Step 3 - Implement calculate_wall_height()
// Calculate wall height based on distance (static for now)
/*
static int	calculate_wall_height(t_game *game, int ray_index)
{
	// STATIC TEST DATA: Create varying wall heights
	// TODO: Replace with actual distance calculation: wall_height = screen_height / distance
	int base_height = game->data->wind_h / 3;  // Base wall height
	int variation = (ray_index % 200) - 100;   // Add some variation

	return (base_height + variation);
}
*/

// TODO: Step 4 - Implement calculate_wall_hit_x()
// Calculate where on the texture to sample (static for now)
/*
static float	calculate_wall_hit_x(int ray_index)
{
	// STATIC TEST DATA: Create texture scrolling effect
	// TODO: Replace with actual hit position from ray data
	return ((float)(ray_index % 64) / 64.0f);  // 0.0 to 1.0 across texture
}
*/

// TODO: Step 5 - Implement draw_textured_wall_column_new()
// Draw a single textured wall column - new version with direct parameters
/*
static void	draw_textured_wall_column_new(t_game *game, int screen_x, int wall_height, float wall_hit_x, mlx_texture_t *texture)
{
	int				wall_start_y, wall_end_y;
	int				y;
	int				tex_x, tex_y;
	double			step;
	uint32_t		color;

	if (!texture || !game->img3D)
		return;

	// Calculate wall boundaries on screen
	wall_start_y = (game->data->wind_h - wall_height) / 2;
	wall_end_y = wall_start_y + wall_height;

	// Clamp to screen boundaries
	if (wall_start_y < 0) wall_start_y = 0;
	if (wall_end_y >= game->data->wind_h) wall_end_y = game->data->wind_h - 1;

	// Calculate texture sampling
	tex_x = (int)(wall_hit_x * texture->width) % texture->width;
	step = (double)texture->height / wall_height;

	// Draw the wall column
	for (y = wall_start_y; y < wall_end_y; y++)
	{
		tex_y = (int)((y - wall_start_y) * step);
		if (tex_y >= (int)texture->height) tex_y = texture->height - 1;

		color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(game->img3D, screen_x, y, color);
	}
}
*/

// TODO: Step 6 - Implement draw_textured_wall_column() (old version)
// Draw a single textured wall column
/*
static void	draw_textured_wall_column(t_game *game, int screen_x, int ray_index)
{
	mlx_texture_t	*texture;
	int				wall_height;
	float			wall_hit_x;
	int				wall_start_y, wall_end_y;
	int				y;
	int				tex_x, tex_y;
	double			step;
	uint32_t		color;

	// Get texture and wall properties
	texture = get_wall_texture(game, ray_index);
	wall_height = calculate_wall_height(game, ray_index);
	wall_hit_x = calculate_wall_hit_x(ray_index);

	// Calculate wall boundaries on screen
	wall_start_y = (game->data->wind_h - wall_height) / 2;
	wall_end_y = wall_start_y + wall_height;

	// Clamp to screen boundaries
	if (wall_start_y < 0) wall_start_y = 0;
	if (wall_end_y >= game->data->wind_h) wall_end_y = game->data->wind_h - 1;

	// Calculate texture sampling
	tex_x = (int)(wall_hit_x * texture->width) % texture->width;
	step = (double)texture->height / wall_height;

	// Draw the wall column
	for (y = wall_start_y; y < wall_end_y; y++)
	{
		tex_y = (int)((y - wall_start_y) * step);
		if (tex_y >= (int)texture->height) tex_y = texture->height - 1;

		color = get_pixel_from_texture(texture, tex_x, tex_y);
		mlx_put_pixel(game->img3D, screen_x, y, color);
	}
}
*/

// TODO: Step 7 - Implement render_3d_walls() (main function)
// Main 3D wall rendering function
// TODO: Replace static test data with real ray data from raycasting
// When ray data is ready, replace the static calculations with:
// - wall_height = calculate_wall_height_from_ray_distance(ray[ray_index].distance)
// - wall_hit_x = ray[ray_index].wall_hit_x (0.0-1.0 where wall was hit)
// - texture = get_texture_from_wall_direction(ray[ray_index].wall_direction) // NO/SO/WE/EA
/*
void	render_3d_walls(t_game *game)
{
	int	screen_x;
	int	wall_height;
	float wall_hit_x;
	mlx_texture_t *texture;

	if (!game || !game->img3D)
		return;

	// For each screen column, draw a textured wall strip with varied test data
	for (screen_x = 0; screen_x < game->data->wind_w; screen_x++)
	{
		// Static test data with variation - will be replaced with real ray data later
		wall_height = 200 + (screen_x % 300) - 150;  // Varied wall heights: 50-350
		wall_hit_x = (screen_x % 100) / 100.0f;      // Wall hit position varies from 0.0 to 0.99

		// Cycle through different textures based on screen position
		if (screen_x < game->data->wind_w / 4)
			texture = game->NO_texture;  // First quarter: North texture
		else if (screen_x < game->data->wind_w / 2)
			texture = game->SO_texture;  // Second quarter: South texture
		else if (screen_x < 3 * game->data->wind_w / 4)
			texture = game->WE_texture;  // Third quarter: West texture
		else
			texture = game->EA_texture;  // Last quarter: East texture

		// Draw the textured wall column
		draw_textured_wall_column_new(game, screen_x, wall_height, wall_hit_x, texture);
	}
}
*/
