/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundaries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:35:22 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/29 06:30:05 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	update_geometry(t_fractal *fr);
void	move_fractal(t_fractal *fr, mlx_key_data_t keydata);
void	move_bounds(t_fractal *fr, mlx_key_data_t keydata);
void	ft_zoom(t_fractal *fr, double ydelta);
void	reset_bounds(t_fractal *fr);

void	update_geometry(t_fractal *fr)
{
	fr->center.rl = (fr->rbound + fr->lbound) / 2;
	fr->center.im = (fr->tbound + fr->bbound) / 2;
	fr->plot_radius_x = (fr->rbound - fr->lbound) / 2;
	fr->plot_radius_y = (fr->tbound - fr->bbound) / 2;
	fr->offset.rl = 2 * fr->plot_radius_x * MOVE_SPEED;
	fr->offset.im = 2 * fr->plot_radius_y * MOVE_SPEED;
}

void	move_fractal(t_fractal *fr, mlx_key_data_t keydata)
{
	update_geometry(fr);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		fr->tbound -= fr->offset.im;
		fr->bbound -= fr->offset.im;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		fr->tbound += fr->offset.im;
		fr->bbound += fr->offset.im;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		fr->rbound += fr->offset.rl;
		fr->lbound += fr->offset.rl;
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		fr->rbound -= fr->offset.rl;
		fr->lbound -= fr->offset.rl;
	}
}

void	move_bounds(t_fractal *fr, mlx_key_data_t keydata)
{
	update_geometry(fr);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		fr->tbound += fr->offset.im;
		fr->bbound += fr->offset.im;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		fr->tbound -= fr->offset.im;
		fr->bbound -= fr->offset.im;
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		fr->rbound -= fr->offset.rl;
		fr->lbound -= fr->offset.rl;
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		fr->rbound += fr->offset.rl;
		fr->lbound += fr->offset.rl;
	}
}

void	ft_zoom(t_fractal *fr, double ydelta)
{
	t_zoom	zm;
	double	zoom;

	zoom = 1;
	update_geometry(fr);
	if (ydelta < 0)
		zoom = 1 / MAGNIFICATION;
	else if (ydelta > 0)
		zoom = MAGNIFICATION;
	zm.old_tl.rl = fr->cursor.rl - fr->lbound;
	zm.old_br.rl = fr->rbound - fr->cursor.rl;
	zm.old_tl.im = fr->tbound - fr->cursor.im;
	zm.old_br.im = fr->cursor.im - fr->bbound;
	zm.new_tl.rl = zm.old_tl.rl * zoom;
	zm.new_tl.im = zm.old_tl.im * zoom;
	zm.new_br.rl = zm.old_br.rl * zoom;
	zm.new_br.im = zm.old_br.im * zoom;
	fr->lbound = fr->cursor.rl - zm.new_tl.rl;
	fr->rbound = fr->cursor.rl + zm.new_br.rl;
	fr->tbound = fr->cursor.im + zm.new_tl.im;
	fr->bbound = fr->cursor.im - zm.new_br.im;
}

void	reset_bounds(t_fractal *fr)
{
	fr->iter_rendition = MAX_ITER;
	fr->center.rl = (GRAPH_XMAX + GRAPH_XMIN) / 2;
	fr->center.im = (GRAPH_YMAX + GRAPH_YMIN) / 2;
	fr->plot_radius_x = (GRAPH_XMAX - GRAPH_XMIN) / 2;
	fr->plot_radius_y = (GRAPH_YMAX - GRAPH_YMIN) / 2;
	fr->lbound = fr->center.rl - fr->plot_radius_x;
	fr->rbound = fr->center.rl + fr->plot_radius_x;
	fr->tbound = fr->center.im + fr->plot_radius_y * HEIGHT / WIDTH;
	fr->bbound = fr->center.im - fr->plot_radius_y * HEIGHT / WIDTH;
	fr->color = RED;
}
