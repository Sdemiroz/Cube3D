/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:22:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/09/11 21:38:58 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	game_loop(void *param);

static void	handle_player_movements(t_game *game);
static bool	turn_player(t_game *game);
static bool	move_player(t_game *game);
static bool	apply_movement(t_game *game, t_data *data, double move_step);
static void	print_fps(t_data *data);

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	
	handle_player_movements(game);
	render_graphics(game);
	print_fps(game->data);
}

static void	handle_player_movements(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) ||
			mlx_is_key_down(game->mlx, MLX_KEY_Q) ||
			mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) ||
			mlx_is_key_down(game->mlx, MLX_KEY_E))
		turn_player(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) ||
			mlx_is_key_down(game->mlx, MLX_KEY_A) ||
			mlx_is_key_down(game->mlx, MLX_KEY_S) ||
			mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game);
}

static bool	turn_player(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	double		rotation;
	bool		fast;

	data = game->data;
	pl = game->player;
	rotation = PI / 180;							// Rotation in radians equivalent to 1 degrees
	fast = (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT));		// Check if shift is pressed
	if (fast)
		rotation *= 4;	 						// Increase rotation speed when shift is pressed
	data->prev_dir = data->cur_dir;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) ||
			mlx_is_key_down(game->mlx, MLX_KEY_Q))
		data->cur_dir += rotation;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) ||
			mlx_is_key_down(game->mlx, MLX_KEY_E))
		data->cur_dir -= rotation;
	if (data->cur_dir < 0)
		data->cur_dir += 2 * PI; 				// Normalize to [0, 2*PI]
	else if (data->cur_dir >= 2 * PI)
		data->cur_dir -= 2 * PI;				// Normalize to [0, 2*PI]
	erase_prev_direction(pl, data);
	erase_previous_fov(pl, pl->rays);
	erase_3d_walls(game);
	udpate_rays(pl->rays, game->map, data);
	draw_3d_walls(game);
	draw_current_fov(pl, pl->rays);
	draw_cur_direction(pl, data);

	return (true);
}

static bool	move_player(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	double		move_step;
	bool		is_running;

	data = game->data;
	pl = game->player;
	move_step = 1; // Define a step size for movement
	is_running = (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)); // Check if shift is pressed
	if (is_running)
		move_step *= 5; // Increase step size when running
	erase_prev_direction(pl, data);
	erase_previous_fov(pl, pl->rays);
	erase_3d_walls(game);
	if (apply_movement(game, data, move_step))
		cast_rays(pl->map, pl->rays, data);
	draw_3d_walls(game);
	draw_current_fov(pl, pl->rays);
	draw_cur_direction(pl, data);

	return (true);
}

static bool	apply_movement(t_game *game, t_data *data, double move_step)
{
	double	base_posx;
	double	base_posy;
	double	move_x;
	double	move_y;
	double	final_posx;
	double	final_posy;
	int		step_half;
	bool	moved;
	t_map	*map;

	base_posx = data->pl_posx_d;
	base_posy = data->pl_posy_d;
	move_x = 0.0;
	move_y = 0.0;
	step_half = data->tile_size / 2;
	moved = false;
	map = game->map;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_x += data->cosine * move_step;
		move_y -= data->sine * move_step;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_x -= data->cosine * move_step;
		move_y += data->sine * move_step;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_x -= data->sine * move_step;
		move_y -= data->cosine * move_step;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_x += data->sine * move_step;
		move_y += data->cosine * move_step;
	}

	final_posx = base_posx;
	final_posy = base_posy;
	if (move_x == 0.0 && move_y == 0.0)
		return (false);
	if (!map || map->img_array == NULL)
		return (false);
	if (move_x != 0.0)
	{
		double	candidate_x;
		double	center_x;
		double	center_y;

		candidate_x = base_posx + move_x;
		center_x = candidate_x + step_half;
		center_y = base_posy + step_half;
		if (!wall_collision_circle(map, center_x, center_y))
			final_posx = candidate_x;
	}
	if (move_y != 0.0)
	{
		double	candidate_y;
		double	center_x;
		double	center_y;

		candidate_y = base_posy + move_y;
		center_x = final_posx + step_half;
		center_y = candidate_y + step_half;
		if (!wall_collision_circle(map, center_x, center_y))
			final_posy = candidate_y;
	}

	if (final_posx != data->pl_posx_d)
	{
		data->pl_posx_d = final_posx;
		data->pl_center_x_d = final_posx + step_half;
		data->pl_posx = (int)lround(final_posx);
		data->pl_center_x = data->pl_posx + step_half;
		moved = true;
	}
	if (final_posy != data->pl_posy_d)
	{
		data->pl_posy_d = final_posy;
		data->pl_center_y_d = final_posy + step_half;
		data->pl_posy = (int)lround(final_posy);
		data->pl_center_y = data->pl_posy + step_half;
		moved = true;
	}

	return (moved);
}

static void	print_fps(t_data *data)
{
	double	time_current;
	double	time_delta;
	
	data->fps++;
	time_current = mlx_get_time();
	time_delta = time_current - data->time;
	data->acc_time += time_delta;
	data->time = time_current;
	if (data->acc_time >= 1.0)
	{
		printf("FPS: %d\n", data->fps);
		data->acc_time = 0;
		data->fps = 0;
	}
}
