/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 05:02:48 by pamatya           #+#    #+#             */
/*   Updated: 2024/07/29 05:16:14 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	render_fractals(void *f);
void	render_mandelbrot(t_fractal *fr);
void	render_julia(t_fractal *fr);
void	render_burning_ship(t_fractal *fr);

void	render_fractals(void *f)
{
	t_fractal	*fr;

	fr = (t_fractal *)f;
	if (fr->mode == 1)
		render_mandelbrot(fr);
	else if (fr->mode == 2)
		render_julia(fr);
	else if (fr->mode == 3)
		render_burning_ship(fr);
}

void	render_mandelbrot(t_fractal *fr)
{
	int		dim[2];
	int		esc_val;
	int		color;
	t_cmplx	tmp;

	dim[0] = 0;
	while (dim[0] < (int)fr->img->height)
	{
		dim[1] = 0;
		while (dim[1] < (int)fr->img->width)
		{
			tmp.rl = dim[1];
			tmp.im = dim[0];
			fr->c.rl = scale_p(tmp.rl, fr->img->width, fr->lbound, fr->rbound);
			fr->c.im = scale_p(tmp.im, fr->img->height, fr->tbound, fr->bbound);
			esc_val = blast_off(fr);
			color = scale_color(esc_val, fr->iter_rendition, fr);
			mlx_put_pixel(fr->img, dim[1], dim[0], color);
			dim[1]++;
		}
		dim[0]++;
	}
}

void	render_julia(t_fractal *fr)
{
	int		dim[2];
	int		escape_val;
	int		color;
	t_cmplx	tmp;

	dim[0] = 0;
	while (dim[0] < (int)fr->img->height)
	{
		dim[1] = 0;
		while (dim[1] < (int)fr->img->width)
		{
			tmp.rl = dim[1];
			tmp.im = dim[0];
			fr->z.rl = scale_p(tmp.rl, fr->img->width, fr->lbound, fr->rbound);
			fr->z.im = scale_p(tmp.im, fr->img->height, fr->tbound, fr->bbound);
			escape_val = blast_off(fr);
			color = scale_color(escape_val, fr->iter_rendition, fr);
			mlx_put_pixel(fr->img, dim[1], dim[0], color);
			dim[1]++;
		}
		dim[0]++;
	}
}

void	render_burning_ship(t_fractal *fr)
{
	int		dim[2];
	int		escape_val;
	int		color;
	t_cmplx	tmp;

	dim[0] = 0;
	while (dim[0] < (int)fr->img->height)
	{
		dim[1] = 0;
		while (dim[1] < (int)fr->img->width)
		{
			tmp.rl = dim[1];
			tmp.im = dim[0];
			fr->c.rl = scale_p(tmp.rl, fr->img->width, fr->lbound, fr->rbound);
			fr->c.im = scale_p(tmp.im, fr->img->height, fr->tbound, fr->bbound);
			escape_val = blast_off(fr);
			color = scale_color(escape_val, fr->iter_rendition, fr);
			mlx_put_pixel(fr->img, dim[1], dim[0], color);
			dim[1]++;
		}
		dim[0]++;
	}
}
