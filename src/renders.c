/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/10 03:45:06 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		render_overview(t_game *game, char *path_to_map);
// static void	place_block(int hor, int vert, int block_color, int offset);
static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int color);

/* -------------------------------------------------------------------------- */
static void	draw_filled_circle(t_img *img, int center_x, int center_y, int radius, uint32_t color);
static void	draw_horizontal_line(t_img *img, int x1, int x2, int y, uint32_t color);
static void	draw_filled_circle_simple(t_img *img, int center_x, int center_y, int radius, uint32_t color);
static void	place_circle(t_img *img, int center_x, int center_y, int radius, uint32_t color);
// static void	draw_player(t_game *game);
/* -------------------------------------------------------------------------- */

void	render_overview(t_game *game, char *path_to_map)
{
	char	*map_layer;
	int		i;
	int		j;
	
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	map_layer = get_next_line(game->map->fd);
	if (!map_layer)
		exit_early(game, "map_layer: gnl", EXIT_FAILURE);
	i = -1;
	j = 0;
	while (map_layer)
	{
		i = -1;
		while (*(map_layer + ++i))
		{
			if (*(map_layer + i) == '1')
				place_block(game->map->overview, i, j, STONE_GRAY);
			else if (*(map_layer + i) == '0')
				place_block(game->map->overview, i, j, 0);
			// usleep(200);
			// if (mlx_image_to_window(game->mlx, game->map->overview, 0, 0) < 0)
			// 	exit_early(game, "Image to window failed", EXIT_FAILURE);
		}
		free(map_layer);
		map_layer = get_next_line(game->map->fd);
		j++;
	}
	draw_border(game->map->overview, MAP_W, MAP_H, SAND_YELLOW);
	draw_filled_circle(game->map->overview, START_PX, START_PY, PLAYER_DIA / 2, DEBUG_RED);
	place_circle(game->map->overview, START_PY, 150, PLAYER_DIA / 2, DEBUG_RED);
}

/*
Function to place a block/tile of size as defined in the HEADER as BLOCK_SIZE
  - if block color is provided as 0, then block_color will be white
  - x and y are the starting coordinates (from upper left corner) of blocks in a
  	tiled world representing the whole block of several pixels BLOCK_SIZE in 
	width and height
*/
static void	place_block(t_img *img, int x, int y, int block_color)
{
	int		i;
	int		j;

	if (!block_color)
		block_color = WHITE;
	j = -1;
	while (++j < BLOCK_SIZE)
	{
		i = -1;
		while (++i < BLOCK_SIZE)
			mlx_put_pixel(img, x * BLOCK_SIZE + i, y * BLOCK_SIZE + j,
					block_color);
	}
}

static void	draw_border(t_img *img, int	width, int height, int color)
{
	int i;
	int	j;
	int	block_x;
	int	block_y;

	i = -1;
	j = -1;
	block_x = width / BLOCK_SIZE;
	block_y = height / BLOCK_SIZE;
	
	while (++j < block_y)
	{
		i = -1;
		if (j == 0 || j == (block_y - 1))
		{
			while (++i < block_x)
				place_block(img, i, j, color);
		}
		else
		{
			while (++i < block_x)
			{
				if (i == 0 || i == (block_x - 1))
					place_block(img, i, j, color);
			}
		}
	}
}



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
//     int player_x = game->player->start_x;
//     int player_y = game->player->start_y;
    
//     // Convert to minimap coordinates
//     int map_x = player_x * BLOCK_SIZE + MAP_OFFSET_X;
//     int map_y = player_y * BLOCK_SIZE + MAP_OFFSET_Y;
    
//     // Draw filled circle for player
//     draw_filled_circle_simple(game->map->overview, map_x, map_y, PLAYER_DIA / 2, PLAYER_COLOR);
// }

void place_circle(t_img *img, int center_x, int center_y, int radius, uint32_t color)
{
    draw_filled_circle_simple(img, center_x, center_y, radius, color);
}
