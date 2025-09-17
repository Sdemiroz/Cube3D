/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:22:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/09/14 14:03:37 by pamatya          ###   ########.fr       */
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

	// move_step = WALK; // Define a step size for movement
	// is_running = (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)); // Check if shift is pressed
	// if (is_running)
	// 	move_step = RUN; // Increase step size when running

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

// static bool	apply_movement(t_game *game, t_data *data, double move_step)
// {
// 	t_dvec	pos;
// 	t_dvec	center;
// 	int		tile_size;
// 	bool	ret;

// 	ret = false;
// 	pos.x = data->pl_posx;
// 	pos.y = data->pl_posy;
// 	tile_size = data->tile_size;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
// 	{
// 		pos.x += rint(data->cosine * move_step);
// 		pos.y -= rint(data->sine * move_step);
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
// 	{
// 		pos.x -= rint(data->cosine * move_step);
// 		pos.y += rint(data->sine * move_step);
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
// 	{
// 		pos.x += rint(cos(data->cur_dir + PI / 2) * move_step);
// 		pos.y -= rint(sin(data->cur_dir + PI / 2) * move_step);
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
// 	{
// 		pos.x += rint(cos(data->cur_dir + 3 * PI / 2) * move_step);
// 		pos.y -= rint(sin(data->cur_dir + 3 * PI / 2) * move_step);
// 	}
// 	center.x = pos.x + tile_size / 2;
// 	center.y = pos.y + tile_size / 2;
// 	// With new collision detection function, but without bounds check
// 	if (!wall_in_the_way_hori(get_map(), (int)center.x, (int)center.y))
// 	{
// 		data->pl_posx = pos.x;
// 		data->pl_center_x = pos.x + tile_size / 2;
// 		ret = true;
// 	}
// 	if (!wall_in_the_way_vert(get_map(), (int)center.x, (int)center.y))
// 	{
// 		data->pl_posy = pos.y;
// 		data->pl_center_y = pos.y + tile_size / 2;
// 		ret = true;
// 	}
// 	return (ret);
// }

static bool	apply_movement(t_game *game, t_data *data, double move_step)
{
	t_dvec	pos_delta;
	t_dvec	new_pos;
	int		tile_size;
	// double	current_time;
	bool	ret;

	ret = false;
	// current_time = mlx_get_time();
	// data->time_delta = current_time - data->time;
	// data->acc_time += data->time_delta;
	// data->time = current_time;
	pos_delta = (t_dvec){0, 0};							// !!! Check if this is allowed 
	tile_size = data->tile_size;
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		pos_delta.x += data->cosine;  
		pos_delta.y -= data->sine;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		pos_delta.x -= data->cosine;
		pos_delta.y += data->sine;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		pos_delta.x += cos(data->cur_dir + PI / 2);
		pos_delta.y -= sin(data->cur_dir + PI / 2);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		pos_delta.x += cos(data->cur_dir + 3 * PI / 2);
		pos_delta.y -= sin(data->cur_dir + 3 * PI / 2);
	}
	new_pos.x = data->pl_posx + pos_delta.x * move_step;
	new_pos.y = data->pl_posy + pos_delta.y * move_step;
	// new_pos.x = data->pl_posx + pos_delta.x * ft_mind(move_step * data->time_delta, WALKING_CAP);
	// new_pos.y = data->pl_posy + pos_delta.y * ft_mind(move_step * data->time_delta, WALKING_CAP);
	
	// With new collision detection function, but without bounds check
	if (!wall_in_the_way_hori(get_map(), new_pos.x + tile_size / 2, new_pos.y + tile_size / 2))
	{
		// data->pl_posx = rint(new_pos.x);
		// data->pl_center_x = rint(new_pos.x + tile_size / 2);
		data->pl_posx = new_pos.x;
		data->pl_center_x = new_pos.x + tile_size / 2;
		ret = true;
	}
	if (!wall_in_the_way_vert(get_map(), new_pos.x + tile_size / 2, new_pos.y + tile_size / 2))
	{
		// data->pl_posy = rint(new_pos.y);
		// data->pl_center_y = rint(new_pos.y + tile_size / 2);
		data->pl_posy = new_pos.y;
		data->pl_center_y = new_pos.y + tile_size / 2;
		ret = true;
	}
	return (ret);
}
 
static void	print_fps(t_data *data)
{
	double	time_current;
	
	data->fps++;
	time_current = mlx_get_time();
	data->time_delta = time_current - data->time;
	data->acc_time += data->time_delta;
	data->time = time_current;
	if (data->acc_time >= 1.0)
	{
		printf("FPS: %d\n", data->fps);
		data->acc_time = 0;
		data->fps = 0;
	}
}
