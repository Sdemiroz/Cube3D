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
static int	apply_movement(t_data *data, double move_step, t_key keydata);
static void turn_player(t_game *game, t_key keydata);

static void	toggle_fov(t_game *game);

// Debugging functions
static void	move_view(t_game *game, t_key keydata);


void	init_events(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_hook(game->mlx, &init_graphics_rendering, param);
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
	else if (((keydata.key == MLX_KEY_I) &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_K &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_J &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) ||
			(keydata.key == MLX_KEY_L &&
			(keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		move_view(game, keydata);
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
	reset_3d_walls(game);
	if (apply_movement(data, move_step, keydata))
		cast_rays(pl->map, pl->rays, data);
	draw_3d_walls(game);
	draw_current_fov(pl, pl->rays);
	draw_cur_direction(pl, data);
}

static int	apply_movement(t_data *data, double move_step, t_key keydata)
{
	int	posx;
	int	posy;
	int	boundx[2];
	int	boundy[2];
	int	center_x;
	int	center_y;
	int	tile_size;
	int	ret;

	ret = 0;
	
	posx = data->pl_posx;
	posy = data->pl_posy;
	tile_size = data->tile_size;

	boundx[0] = tile_size;
	boundx[1] = data->mmp_w - tile_size;
	boundy[0] = tile_size;
	boundy[1] = data->mmp_h - tile_size;

	if (keydata.key == MLX_KEY_W)
	{
		posx += (int)rint(data->cosine * move_step);
		posy -= (int)rint(data->sine * move_step);
	}
	else if (keydata.key == MLX_KEY_S)
	{
		posx -= (int)rint(data->cosine * move_step);
		posy += (int)rint(data->sine * move_step);
	}
	else if (keydata.key == MLX_KEY_A)
	{
		posx += (int)rint(cos(data->cur_dir + PI / 2) * move_step);
		posy -= (int)rint(sin(data->cur_dir + PI / 2) * move_step);
	}
	else if (keydata.key == MLX_KEY_D)
	{
		posx += (int)rint(cos(data->cur_dir + 3 * PI / 2) * move_step);
		posy -= (int)rint(sin(data->cur_dir + 3 * PI / 2) * move_step);
	}
	center_x = posx + tile_size / 2;
	center_y = posy + tile_size / 2;

	// With new collision detection function, but without bounds check
	if (!wall_in_the_way_hori(get_map(), center_x, center_y))
	{
		data->pl_posx = posx;
		data->pl_center_x = posx + tile_size / 2;
		ret = 1;
	}
	if (!wall_in_the_way_vert(get_map(), center_x, center_y))
	{
		data->pl_posy = posy;
		data->pl_center_y = posy + tile_size / 2;
		ret = 1;
	}

	// test_print_bounds(boundx, boundy);

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
	reset_3d_walls(game);
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

static void	move_view(t_game *game, t_key keydata)
{
	t_data	*data;
	int		move_step;
	bool	is_running;
	int		view_posx;
	int		view_posy;

	data = game->data;
	move_step = 2; // Define a step size for movement
	is_running = (keydata.modifier & MLX_SHIFT); // Check if shift is pressed
	if (is_running)
		move_step *= 5; // Increase step size when running

	view_posx = data->debug_offset_x;
	view_posy = data->debug_offset_y;

	if (keydata.key == MLX_KEY_I)
		view_posy -= move_step;
	else if (keydata.key == MLX_KEY_K)
		view_posy += move_step;	
	else if (keydata.key == MLX_KEY_J)
		view_posx -= move_step;
	else if (keydata.key == MLX_KEY_L)
		view_posx += move_step;

	data->debug_offset_x = view_posx;
	data->debug_offset_y = view_posy;
}
