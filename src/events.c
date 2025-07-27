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
static void turn_player(void *param, t_key keydata);

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
	else if ((keydata.key == MLX_KEY_LEFT &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
			|| (keydata.key == MLX_KEY_RIGHT &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		turn_player(param, keydata);
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
	t_data	*data;
	double	move_step;
	bool	is_running;

	game = (t_game *)param;
	data = game->data;
	move_step = 3; // Define a step size for movement
	is_running = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
	if (is_running)
		move_step *= 5; // Increase step size when running

	erase_previous_ray(game->rays, data);
	if (keydata.key == MLX_KEY_W)
	{
		data->pl_posx += (int)rint(data->cosine * move_step);
		data->pl_posy -= (int)rint(data->sine * move_step);
	}
	if (keydata.key == MLX_KEY_S)
	{
		data->pl_posx -= (int)rint(data->cosine * move_step);
		data->pl_posy += (int)rint(data->sine * move_step);
	}
	if (keydata.key == MLX_KEY_A)
	{
		data->pl_posx += (int)rint(cos(data->cur_dir + PI / 2) * move_step);
		data->pl_posy -= (int)rint(sin(data->cur_dir + PI / 2) * move_step);
	}
	if (keydata.key == MLX_KEY_D)
	{
		data->pl_posx += (int)rint(cos(data->cur_dir + 3 * PI / 2) * move_step);
		data->pl_posy -= (int)rint(sin(data->cur_dir + 3 * PI / 2) * move_step);
	}
	draw_forward_ray(game->rays, data);
}

static void turn_player(void *param, t_key keydata)
{
	t_game	*game;
	t_data	*data;
	float	rotation;
	bool	fast;

	game = (t_game *)param;
	data = game->data;
	rotation = (2 * PI / 360) * 5;	// Rotation in radians equivalent to 5 degrees

	fast = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
	if (fast)
		rotation *= 4;	 // Increase rotation speed when shift is pressed

	if (keydata.key == MLX_KEY_LEFT)
		data->cur_dir += rotation;
	else if (keydata.key == MLX_KEY_RIGHT)
		data->cur_dir -= rotation;

	draw_player_direction(game->rays, data);
}

// // Function to determine before a movement if the player has collided with a wall
// static bool	has_space_to_move(t_game *game, int new_x, int new_y)
// {
// 	t_data	*data;
// 	t_map	*map;
// 	int		block_x;
// 	int		block_y;

	


// 	return (false); // No collision
// }
