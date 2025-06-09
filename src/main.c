/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/06/09 16:01:49 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

typedef struct s_game {
    mlx_t*      mlx;
    mlx_image_t* img;
    int         dot_x;
    int         dot_y;
} t_game;

// Key hook function to handle input
void key_hook(mlx_key_data_t keydata, void* param)
{
    t_game* game = (t_game*)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
}

// Loop hook function called every frame
void update_game(void* param)
{
    t_game* game = (t_game*)param;

    // Clear previous dot position
    ft_memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(int32_t));

    // Check for continuous key presses
    if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
        game->dot_y -= 4;
    if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
        game->dot_y += 4;
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        game->dot_x -= 4;
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        game->dot_x += 4;

    // Boundary checking
    if (game->dot_x < 0) game->dot_x = 10;
    if (game->dot_y < 0) game->dot_y = 10;
    if (game->dot_x >= (int)game->img->width) game->dot_x = (int)game->img->width - 10;
    if (game->dot_y >= (int)game->img->height) game->dot_y = (int)game->img->height - 10;

    // Draw new dot (simple 3x3 square)
    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            int px = game->dot_x + x;
            int py = game->dot_y + y;
            if (px >= 0 && px < (int)game->img->width && py >= 0 && py < (int)game->img->height) {
                mlx_put_pixel(game->img, (uint32_t)px, (uint32_t)py, 0xFF0000FF); // Red dot
            }
        }
    }
}

int main(int argc, char **argv)
{
    (void)argv;
    (void)argc;
    gc_init_garbage_collector();

    t_game game;

    // Initialize MLX
    game.mlx = mlx_init(800, 600, "Cube3D - Controllable Dot", true);
    if (!game.mlx)
    {
        ft_printf("Error: Failed to initialize MLX\n");
        return (1);
    }

    // Create an image
    game.img = mlx_new_image(game.mlx, 800, 600);
    if (!game.img)
    {
        ft_printf("Error: Failed to create image\n");
        mlx_terminate(game.mlx);
        return (1);
    }

    // Initialize dot position
    game.dot_x = 400;
    game.dot_y = 300;

    // Clear the image (black background)
    ft_memset(game.img->pixels, 0, game.img->width * game.img->height * sizeof(int32_t));

    // Draw initial dot
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            mlx_put_pixel(game.img, (uint32_t)(game.dot_x + x), (uint32_t)(game.dot_y + y), 0xFF0000FF);
        }
    }

    // Display the image
    if (mlx_image_to_window(game.mlx, game.img, 0, 0) == -1)
    {
        ft_printf("Error: Failed to display image\n");
        mlx_delete_image(game.mlx, game.img);
        mlx_terminate(game.mlx);
        return (1);
    }

    // Set key hook for ESC key
    mlx_key_hook(game.mlx, &key_hook, &game);

    // Set loop hook for continuous movement
    mlx_loop_hook(game.mlx, &update_game, &game);

    // Start the loop
    mlx_loop(game.mlx);

    // Cleanup
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);

    return (0);
}
