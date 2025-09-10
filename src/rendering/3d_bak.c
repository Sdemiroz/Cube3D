/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_bak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:20:14 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/09/09 22:09:14 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
`get_pixel_from_texture(texture, x, y)`
Extracts RGBA color from texture at given coordinates with bounds checking.
*/
uint32_t	get_pixel_from_texture(t_txr *texture, int x, int y)
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

/*
`draw_column(game, screen_x, wall_height, wall_hit_x, texture)`
Renders a single vertical column with:
- `x`: Screen column position
- `wall_height`: Height of wall in pixels (affects distance/perspective)
- `wall_hit_x`: Texture X coordinate (0.0-1.0) where ray hit the wall
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
	if (wall_start_y < 0) wall_start_y = 0;
	if (wall_end_y >= game->data->wind_h) wall_end_y = game->data->wind_h - 1;
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
	t_txr 		*texture;

	screen_x = 0;

	if (!game || !game->img3D)
		exit_early(game, "render_3d_walls: Invalid game or img3D", EXIT_FAILURE);
	while (screen_x < game->data->wind_w)
	{
		// Static test data
		wall_height = 200 + (screen_x % 300) - 150;
		wall_hit_x = (screen_x % 100) / 100.0f;
		if (screen_x < game->data->wind_w / 4)
			texture = game->NO_texture;
		else if (screen_x < game->data->wind_w / 2)
			texture = game->SO_texture;
		else if (screen_x < 3 * game->data->wind_w / 4)
			texture = game->WE_texture;
		else
			texture = game->EA_texture;
		draw_column(game, screen_x, wall_height, wall_hit_x, texture);
		screen_x++;
	}
}


// static mlx_texture_t	*get_wall_texture(t_game *game, int ray_index)
// {
// 	// STATIC TEST DATA: Cycle through different wall types
// 	// TODO: Replace with actual wall direction from ray data
// 	int wall_type = ray_index % 4;

// 	switch (wall_type)
// 	{
// 		case 0: return (game->NO_texture);  // North wall
// 		case 1: return (game->SO_texture);  // South wall
// 		case 2: return (game->WE_texture);  // West wall
// 		case 3: return (game->EA_texture);  // East wall
// 		default: return (game->NO_texture);
// 	}
// }

// static int	calculate_wall_height(t_game *game, int ray_index)
// {
// 	// STATIC TEST DATA: Create varying wall heights
// 	// TODO: Replace with actual distance calculation: wall_height = screen_height / distance
// 	int base_height = game->data->wind_h / 3;  // Base wall height
// 	int variation = (ray_index % 200) - 100;   // Add some variation

// 	return (base_height + variation);
// }

// static float	calculate_wall_hit_x(int ray_index)
// {
// 	// STATIC TEST DATA: Create texture scrolling effect
// 	// TODO: Replace with actual hit position from ray data
// 	return ((float)(ray_index % 64) / 64.0f);  // 0.0 to 1.0 across texture
// }
