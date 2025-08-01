/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/01 03:42:41 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * BACKGROUND IMAGE IMPLEMENTATION GUIDE - by GitHub Copilot
 * ============================================================================
 *
 * GOAL: Create a background image with ceiling color on top half and floor
 *       color on bottom half, covering the entire window, rendered first.
 *
 * STEP-BY-STEP IMPLEMENTATION:
 *
 * 1. STRUCT MODIFICATIONS (include/cub3d.h):
 *    - Add to t_game struct:
 *      * t_img *background;           // background image pointer
 *      * int32_t background_inst_id;  // MLX instance ID for background
 *    - Add function declaration:
 *      * void init_background(t_game *game);
 *
 * 2. INITIALIZATION (src/initialization/init_game.c):
 *    a) In init_game() function:
 *       - Initialize background_inst_id = -1 in struct initialization
 *       - Create background image: mlx_new_image(mlx, width, height)
 *       - Add error handling for image creation
 *
 *    b) In init_minimap() function:
 *       - Call init_background(game) AFTER parse_game_data()
 *       - This ensures ceiling_color and floor_color are available
 *
 *    c) Create init_background() function:
 *       - Get window dimensions (wind_w, wind_h)
 *       - Convert RGB to RGBA: (R << 24) | (G << 16) | (B << 8) | 0xFF
 *       - Use nested loops to fill pixels:
 *         * for (y = 0; y < height; y++)
 *         *   for (x = 0; x < width; x++)
 *         *     if (y < height/2) mlx_put_pixel(background, x, y, ceiling_rgba)
 *         *     else              mlx_put_pixel(background, x, y, floor_rgba)
 *
 * 3. RENDERING (src/rendering/renders.c):
 *    a) Add render_background() function declaration
 *    b) In init_graphics_rendering():
 *       - Call render_background(game) FIRST (before other renders)
 *    c) Create render_background() function:
 *       - Check if already rendered (background_inst_id == -1)
 *       - Use mlx_image_to_window(mlx, background, 0, 0)
 *       - Store instance ID and handle errors
 *
 * 4. CLEANUP (src/utils/error.c):
 *    - In clear_mlx() function:
 *      * Add: if (game->background) mlx_delete_image(mlx, background);
 *
 * KEY CONCEPTS:
 * - MLX42 uses RGBA format (Red, Green, Blue, Alpha channels)
 * - Rendering order matters: background first, then other elements
 * - Colors come from parsed .cub file (F and C lines)
 * - Instance IDs track rendered images for cleanup
 * - Error handling is crucial for MLX operations
 *
 * DEBUGGING TIPS:
 * - Add printf statements to verify color parsing
 * - Check if background image is created successfully
 * - Ensure background is rendered before other elements
 * - Verify window dimensions match image dimensions
 * ============================================================================
 */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	gc_init_garbage_collector();
	if (argc != 2)
		exit_early(NULL, "Error, Invalid Argument\n", 1);
	ft_bzero(&game, sizeof(t_game));
	init_game_elements(&game, argv[1]);
	printf("Let the games begin!!!\n");
	game_start(&game);
	init_events((void *)&game);
	mlx_loop((game).mlx);
	mlx_terminate(game.mlx);

	gc_free_all();
    return(0);
}
