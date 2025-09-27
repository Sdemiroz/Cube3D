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

static void	move_player(t_game *game, t_key keydata);
static int	apply_movement(t_data *data, t_map *map, double move_step, t_key keydata);
static void turn_player(t_game *game, t_key keydata);

static void	toggle_fov(t_game *game);

// Debugging functions
// static void	move_view(t_game *game, t_key keydata);


void	init_events(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_hook(game->mlx, &render_graphics, param);
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
		move_player(game, keydata);
	else if ((keydata.key == MLX_KEY_LEFT &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
			|| (keydata.key == MLX_KEY_RIGHT &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		turn_player(game, keydata);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		toggle_fov(game);
	// else if (((keydata.key == MLX_KEY_I) &&
	// 		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
	// 		(keydata.key == MLX_KEY_K &&
	// 		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
	// 		(keydata.key == MLX_KEY_J &&
	// 		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
	// 		(keydata.key == MLX_KEY_L &&
	// 		(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
	// 	move_view(game, keydata);
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

static void	move_player(t_game *game, t_key keydata)
{
	t_data		*data;
	t_player	*pl;
	double		move_step;
	bool		is_running;

	data = game->data;
	pl = game->player;
	move_step = 2; // Define a step size for movement
	is_running = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
	if (is_running)
		move_step *= 5; // Increase step size when running
	erase_prev_direction(pl, data);
	erase_previous_fov(pl, pl->rays);
	erase_3d_walls(game);
	if (apply_movement(data, pl->map, move_step, keydata))
		cast_rays(pl->map, pl->rays, data);
	draw_3d_walls(game);
	draw_current_fov(pl, pl->rays);
	draw_cur_direction(pl, data);
}

static int	apply_movement(t_data *data, t_map *map, double move_step, t_key keydata)
{
	double	base_posx;
	double	base_posy;
	double	move_x;
	double	move_y;
	double	final_posx;
	double	final_posy;
	int		step_half;
	int		ret;
	base_posx = data->pl_posx_d;
	base_posy = data->pl_posy_d;
	move_x = 0.0;
	move_y = 0.0;
	step_half = data->tile_size / 2;
	ret = 0;

	if (keydata.key == MLX_KEY_W)
	{
		move_x += data->cosine * move_step;
		move_y -= data->sine * move_step;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		move_x -= data->cosine * move_step;
		move_y += data->sine * move_step;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		move_x -= data->sine * move_step;
		move_y -= data->cosine * move_step;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		move_x += data->sine * move_step;
		move_y += data->cosine * move_step;
	}

	final_posx = base_posx;
	final_posy = base_posy;
	if (move_x == 0.0 && move_y == 0.0)
		return (0);
	if (!map || map->img_array == NULL)
		return (0);
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
		ret = 1;
	}
	if (final_posy != data->pl_posy_d)
	{
		data->pl_posy_d = final_posy;
		data->pl_center_y_d = final_posy + step_half;
		data->pl_posy = (int)lround(final_posy);
		data->pl_center_y = data->pl_posy + step_half;
		ret = 1;
	}

	return (ret);
}

static void turn_player(t_game *game, t_key keydata)
{
	t_data		*data;
	t_player	*pl;
	double		rotation;
	bool		fast;

	data = game->data;
	pl = game->player;
	rotation = PI / 36;							// Rotation in radians equivalent to 5 degrees
	fast = (keydata.modifier & MLX_SHIFT);		// Check if shift is pressed
	if (fast)
		rotation *= 4;	 						// Increase rotation speed when shift is pressed
	data->prev_dir = data->cur_dir;
	if (keydata.key == MLX_KEY_LEFT)
		data->cur_dir += rotation;
	else if (keydata.key == MLX_KEY_RIGHT)
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
}

static void	toggle_fov(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	t_rays		**rays;

	data = game->data;
	pl = game->player;
	rays = pl->rays;
	if (data->fov_toggle == true)
	{
		erase_previous_fov(pl, rays);
		data->fov_toggle = false;
	}
	else if (data->fov_toggle == false)
	{
		data->fov_toggle = true;
		draw_current_fov(pl, rays);
	}
	// Redraw direction line to restore any pixels erased by FOV toggle
	draw_cur_direction(pl, data);
}

// static void	move_view(t_game *game, t_key keydata)
// {
// 	t_data	*data;
// 	int		move_step;
// 	bool	is_running;
// 	int		view_posx;
// 	int		view_posy;

// 	data = game->data;
// 	move_step = 2; // Define a step size for movement
// 	is_running = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
// 	if (is_running)
// 		move_step *= 5; // Increase step size when running

// 	view_posx = data->debug_offset_x;
// 	view_posy = data->debug_offset_y;

// 	if (keydata.key == MLX_KEY_I)
// 		view_posy -= move_step;
// 	else if (keydata.key == MLX_KEY_K)
// 		view_posy += move_step;	
// 	else if (keydata.key == MLX_KEY_J)
// 		view_posx -= move_step;
// 	else if (keydata.key == MLX_KEY_L)
// 		view_posx += move_step;

// 	data->debug_offset_x = view_posx;
// 	data->debug_offset_y = view_posy;
// }
