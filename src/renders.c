/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:50:08 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/10 21:01:51 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		render_overview(void *param);
// static void	place_block(int hor, int vert, int block_color, int offset);
static void	place_block(t_img *img, int i, int j, int block_color);
static void	draw_border(t_img *img, int	width, int height, int color);

void	render_overview(void *param)
{
	t_game	*game;
	char	*map_layer;
	int		i;
	int		j;
	
	// game = (t_game *)param;
	game = get_game();
	(void)param;
	map_layer = NULL;
	
	
	// DEBUG: Check if file descriptor is valid
    printf("DEBUG: map->fd = %d\n", game->map->fd);
    if (game->map->fd < 0) {
        printf("ERROR: Invalid file descriptor\n");
        exit_early(game, "Invalid file descriptor", EXIT_FAILURE);
    }
    
    // DEBUG: Test if fd is readable
    if (fcntl(game->map->fd, F_GETFL) == -1) {
        perror("fcntl check failed");
        exit_early(game, "File descriptor not accessible", EXIT_FAILURE);
	}
		
	map_layer = get_next_line(game->map->fd);
	if (!map_layer)
	{
		printf("Exiting over here\n");
		exit_early(game, "map_layer: gnl", EXIT_FAILURE);
	}
	
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
			printf("I am in the inner loop\n");
		}
		free(map_layer);
		map_layer = get_next_line(game->map->fd);
		j++;
		printf("I am in the loop\n");
	}
	draw_border(game->img_3d, WIDTH, HEIGHT, RED);
	draw_border(game->map->overview, MAP_W, MAP_H, SAND_YELLOW);
	place_player(game, 1);
	sleep(5);
	if (mlx_image_to_window(game->mlx, game->img_3d, 0, 0) < 0)
		exit_early(game, "Image to window failed", EXIT_FAILURE);

	sleep(5);
	
	if (mlx_image_to_window(game->mlx, game->map->overview, MAP_OFFSET_X, MAP_OFFSET_Y) < 0)
		exit_early(game, "Image to window failed", EXIT_FAILURE);
	printf("It reached here the first time\n");
	sleep(5);
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
		return ;
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
