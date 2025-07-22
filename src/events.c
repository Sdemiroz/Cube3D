/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:08:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/07 18:13:01 by pamatya          ###   ########.game       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_events(void *param);

static void	upon_press(t_key keydata, void *param);
// static void	upon_scroll(double xdelta, double ydelta, void *param);
static void	upon_close(void *param);

static void	move_player(void *param, t_key keydata);
static bool	has_space_to_move(t_game *game, int new_x, int new_y);

void	init_events(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_hook(game->mlx, &render_map, param);
	// mlx_scroll_hook(game->mlx, &upon_scroll, game);
	mlx_key_hook(game->mlx, &upon_press, param);
	mlx_close_hook(game->mlx, &upon_close, param);
}

static void	upon_press(t_key keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		upon_close(param);
	else if (((keydata.key == MLX_KEY_W) &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_S &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_A &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_D &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		move_player(param, keydata);
	// else if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	// 	|| (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	// 	|| (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	// 	|| (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS))
	// 	rotate_player(game, keydata);
	// else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	// 	reset_bounds(game);
}

// static void	upon_scroll(double xdelta, double ydelta, void *param)
// {
// 	t_game	*game;
// 	int			cursor_x;
// 	int			cursor_y;

// 	game = (t_game *)param;
// 	(void)xdelta;
// 	mlx_get_mouse_pos(game->mlx, &cursor_x, &cursor_y);
// 	game->cursor.rl = scale_p(cursor_x, WIDTH, game->lbound, game->rbound);
// 	game->cursor.im = scale_p(cursor_y, HEIGHT, game->tbound, game->bbound);
// 	if (ydelta < 0 || ydelta > 0)
// 		ft_zoom(game, ydelta);
// }

static void	upon_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	exit_early(game, NULL, EXIT_SUCCESS);
}

static void	move_player(void *param, t_key keydata)
{
	t_game	*game;
	t_map	*map;
	int		move_step;
	bool	is_running;

	game = (t_game *)param;
	map = game->map;
	move_step = 1; // Define a step size for movement	
	is_running = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
	if (is_running)
		move_step = 5; // Increase step size when running
	if (keydata.key == MLX_KEY_W)
		map->pl_posy -= move_step;
	else if (keydata.key == MLX_KEY_S)
		map->pl_posy += move_step;
	else if (keydata.key == MLX_KEY_A)
		map->pl_posx -= move_step;
	else if (keydata.key == MLX_KEY_D)
		map->pl_posx += move_step;
}

// Function to determine before a movement if the player has collided with a wall
static bool	has_space_to_move(t_game *game, int new_x, int new_y)
{
	t_map	*map;
	int		block_x;
	int		block_y;

	map = game->map;
	block_x = new_x / TILE_SIZE;
	block_y = new_y / TILE_SIZE;

	if (block_x < 0 || block_x >= map->data->tiles_x ||
		block_y < 0 || block_y >= map->data->tiles_y)
		return (false); // Out of bounds

	if (map->map_array[block_y][block_x] == '1')
		return (true); // Collision with wall

	return (false); // No collision
}
