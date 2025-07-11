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
	// t_game	*game;

	// game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		upon_close(param);
	else if ((keydata.key == MLX_KEY_W &&
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

	game = (t_game *)param;
	map = game->map;
	move_step = 1; // Define a step size for movement
	if (keydata.key == MLX_KEY_W)
		map->pl_posy -= move_step;
	else if (keydata.key == MLX_KEY_S)
		map->pl_posy += move_step;
	else if (keydata.key == MLX_KEY_A)
		map->pl_posx -= move_step;
	else if (keydata.key == MLX_KEY_D)
		map->pl_posx += move_step;
}
