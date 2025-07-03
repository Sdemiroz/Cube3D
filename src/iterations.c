/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:39:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/06/17 16:44:19 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

t_cmplx	get_next_iteration(t_cmplx z_n, t_cmplx c);
double	scale_p(double val, double max_val, double sc_min, double sc_max);
int		scale_color(int iter, int max_iter, t_fractal *fr);
int		blast_off(t_fractal *fr);

t_cmplx	get_next_iteration(t_cmplx z_n, t_cmplx c)
{
	t_cmplx	z_nxt;

	z_nxt = c_sqr_plus_const(z_n, c);
	return (z_nxt);
}

// Function to scale the val within the range sc_min and sc_max, using
// linear interpolation
double	scale_p(double val, double max_val, double sc_min, double sc_max)
{
	double	scaled_val;
	double	ratio;

	ratio = (sc_max - sc_min) / (max_val - 0);
	scaled_val = sc_min + val * ratio;
	return (scaled_val);
}

// Similar function as above to scale color as int
int	scale_color(int iter, int max_iter, t_fractal *fr)
{
	int	start_color;
	int	end_color;
	int	scaled_color;
	int	ratio;
	int	color_step;

	start_color = fr->color;
	end_color = WHITE;
	color_step = 1;
	ratio = (end_color - start_color) / (max_iter - 0);
	scaled_color = start_color + iter * color_step * ratio;
	return (scaled_color);
}

// Function to calculate the no. of escape_val to escape the radius
int	blast_off(t_fractal *fr)
{
	int		escape_val;
	t_cmplx	zn;

	zn = fr->z;
	escape_val = 0;
	while (escape_val < fr->iter_rendition && c_dist_sqr(zn) <= fr->bound)
	{
		if (fr->mode == 3)
			zn = c_sqr_plus_const_abs(zn, fr->c);
		else
			zn = c_sqr_plus_const(zn, fr->c);
		escape_val++;
	}
	return (escape_val);
}
