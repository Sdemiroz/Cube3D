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
static void	toggle_fov(t_game *game);

// Debugging functions
// static void	move_view(t_game *game, t_key keydata);


void	init_events(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_hook(game->mlx, &game_loop, param);
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
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		toggle_fov(game);
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
