/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:47:59 by pamatya           #+#    #+#             */
/*   Updated: 2025/06/17 14:02:50 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	upon_press(mlx_key_data_t keydata, void *param);
void	upon_scroll(double xdelta, double ydelta, void *param);
void	upon_close(void *param);
void	change_details(t_fractal *fr, mlx_key_data_t keydata);
void	change_color(t_fractal *fr);

void	upon_press(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fr;

	fr = (t_fractal *)param;
	if ((keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS))
		move_fractal(fr, keydata);
	else if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS))
		move_bounds(fr, keydata);
	else if (((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_P)
		&& keydata.action == MLX_PRESS)
		|| ((keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_O)
		&& keydata.action == MLX_PRESS))
		change_details(fr, keydata);
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		change_color(fr);
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		reset_bounds(fr);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		upon_close(fr);
}

void	upon_scroll(double xdelta, double ydelta, void *param)
{
	t_fractal	*fr;
	int			cursor_x;
	int			cursor_y;

	fr = (t_fractal *)param;
	(void)xdelta;
	mlx_get_mouse_pos(fr->mlx, &cursor_x, &cursor_y);
	fr->cursor.rl = scale_p(cursor_x, WIDTH, fr->lbound, fr->rbound);
	fr->cursor.im = scale_p(cursor_y, HEIGHT, fr->tbound, fr->bbound);
	if (ydelta < 0 || ydelta > 0)
		ft_zoom(fr, ydelta);
}

void	upon_close(void *param)
{
	t_fractal	*fr;

	fr = (t_fractal *)param;
	frexit(NULL, fr, EXIT_SUCCESS);
}

void	change_details(t_fractal *fr, mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_KP_ADD || keydata.key == MLX_KEY_P)
			&& keydata.action == MLX_PRESS)
	{
		fr->iter_rendition += QUALITY_DELTA;	
	}
	else if ((keydata.key == MLX_KEY_KP_SUBTRACT || keydata.key == MLX_KEY_O)
			&& keydata.action == MLX_PRESS)
	{
		if (fr->iter_rendition > QUALITY_DELTA)
			fr->iter_rendition -= QUALITY_DELTA;	
	}
}

void	change_color(t_fractal *fr)
{
	if (fr->color == RED)
		fr->color = GREEN;
	else if (fr->color == GREEN)
		fr->color = BLUE;
	else if (fr->color == BLUE)
		fr->color = YELLOW;
	else if (fr->color == YELLOW)
		fr->color = MAGENTA;
	else if (fr->color == MAGENTA)
		fr->color = CYAN;
	else if (fr->color == CYAN)
		fr->color = PSYCH_VIOLET;
	else if (fr->color == PSYCH_VIOLET)
		fr->color = WHITE;
	else if (fr->color == WHITE)
		fr->color = RED;
}
