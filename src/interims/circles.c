/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:41:41 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/11 01:29:48 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



/* -------------------------------------------------------------------------- */

void draw_filled_circle(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    
    // Draw the initial horizontal lines
    draw_horizontal_line(img, center_x - radius, center_x + radius, center_y, color);
    
    while (x < y)
    {
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            // Draw horizontal lines for the current y level
            draw_horizontal_line(img, center_x - x, center_x + x, center_y + y, color);
            draw_horizontal_line(img, center_x - x, center_x + x, center_y - y, color);
            
            y--;
            d += 2 * (x - y) + 5;
        }
        
        x++;
        
        // Draw horizontal lines for the current x level
        draw_horizontal_line(img, center_x - y, center_x + y, center_y + x, color);
        draw_horizontal_line(img, center_x - y, center_x + y, center_y - x, color);
    }
}

static void draw_horizontal_line(t_img *img, int x1, int x2, int y, uint32_t color)
{
    for (int x = x1; x <= x2; x++)
    {
        if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
            mlx_put_pixel(img, x, y, color);
    }
}

/* -------------------------------------------------------------------------- */

void draw_filled_circle_simple(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    int radius_squared = radius * radius;
    
    for (int y = center_y - radius; y <= center_y + radius; y++)
    {
        for (int x = center_x - radius; x <= center_x + radius; x++)
        {
            int dx = x - center_x;
            int dy = y - center_y;
            
            if (dx * dx + dy * dy <= radius_squared)
            {
                if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
                    mlx_put_pixel(img, x, y, color);
            }
        }
    }
}

// void draw_player(t_game *game)
// {
//     // Get player position (you'll need to implement this based on your player system)
//     int player_x = game->player->pos_x;
//     int player_y = game->player->pos_y;
    
//     // Convert to minimap coordinates
//     int map_x = player_x * BLOCK_SIZE + MAP_OFFSET_X;
//     int map_y = player_y * BLOCK_SIZE + MAP_OFFSET_Y;
    
//     // Draw filled circle for player
//     draw_filled_circle_simple(game->map->image, map_x, map_y, PLAYER_DIA / 2, PLAYER_COLOR);
// }

void place_circle(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    draw_filled_circle_simple(img, center_x, center_y, radius, color);
}

/* -------------------------------------------------------------------------- */
// Improve circle fns

static void draw_filled_circle_smooth(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    float radius_f = (float)radius;
    int radius_ceil = radius + 1; // Check one pixel beyond for smoother edges
    
    for (int y = center_y - radius_ceil; y <= center_y + radius_ceil; y++)
    {
        for (int x = center_x - radius_ceil; x <= center_x + radius_ceil; x++)
        {
            if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
            {
                float dx = (float)(x - center_x);
                float dy = (float)(y - center_y);
                float distance = sqrtf(dx * dx + dy * dy);
                
                if (distance <= radius_f + 0.5f) // Softer boundary
                {
                    // Anti-aliasing: fade pixels near the edge
                    if (distance > radius_f - 0.5f)
                    {
                        float alpha = (radius_f + 0.5f - distance);
                        uint32_t blended_color = blend_color(color, alpha);
                        mlx_put_pixel(img, x, y, blended_color);
                    }
                    else
                    {
                        mlx_put_pixel(img, x, y, color);
                    }
                }
            }
        }
    }
}

// Helper function to blend colors for anti-aliasing
static uint32_t blend_color(uint32_t color, float alpha)
{
    if (alpha >= 1.0f) return color;
    if (alpha <= 0.0f) return 0x00000000; // Transparent
    
    uint8_t r = (uint8_t)((color >> 24) & 0xFF);
    uint8_t g = (uint8_t)((color >> 16) & 0xFF);
    uint8_t b = (uint8_t)((color >> 8) & 0xFF);
    uint8_t original_alpha = (uint8_t)(color & 0xFF);
    
    uint8_t new_alpha = (uint8_t)(original_alpha * alpha);
    
    return (r << 24) | (g << 16) | (b << 8) | new_alpha;
}

/* -------------------------------------------------------------------------- */
// Alternate improve circle fns

static void draw_filled_circle_improved(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    int radius_squared = radius * radius;
    int extended_radius = radius + 1;
    int extended_radius_squared = extended_radius * extended_radius;
    
    for (int y = center_y - extended_radius; y <= center_y + extended_radius; y++)
    {
        for (int x = center_x - extended_radius; x <= center_x + extended_radius; x++)
        {
            if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
            {
                int dx = x - center_x;
                int dy = y - center_y;
                int distance_squared = dx * dx + dy * dy;
                
                // Draw solid pixels within radius
                if (distance_squared <= radius_squared)
                {
                    mlx_put_pixel(img, x, y, color);
                }
                // Add edge pixels for smoother appearance
                else if (distance_squared <= extended_radius_squared)
                {
                    // For small circles, add some edge pixels to make it rounder
                    if (radius <= 5)
                    {
                        uint32_t edge_color = (color & 0xFFFFFF00) | 0x80; // Half transparency
                        mlx_put_pixel(img, x, y, edge_color);
                    }
                }
            }
        }
    }
}
