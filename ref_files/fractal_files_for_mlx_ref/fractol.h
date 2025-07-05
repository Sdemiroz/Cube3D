/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 00:36:33 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/05 20:57:10 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../lib/includes/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define _PRINT 1

# define MAX_ITER 100
# define QUALITY_DELTA 25
# define ESC_RADIUS 2
# define HEIGHT 1000
# define WIDTH 1380
# define GRAPH_XMIN -2
# define GRAPH_XMAX 2
# define GRAPH_YMAX 2
# define GRAPH_YMIN -2
# define MOVE_SPEED 0.1
# define MAGNIFICATION 1.25

// Color definitions: simple RGB
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define PSYCH_VIOLET 0x8B00FF
# define CYAN   0x00FFFF
# define MAGENTA 0xFF00FF
# define YELLOW 0xFFFF00
# define BLUE  0x0000FF
# define GREEN 0x00FF00
# define RED   0xFF0000

typedef struct s_cmplx
{
	double	rl;
	double	im;
}	t_cmplx;

typedef struct s_zoom
{
	t_cmplx	old_tl;
	t_cmplx	old_br;
	t_cmplx	new_tl;
	t_cmplx	new_br;
}	t_zoom;
typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		*name;
	int			mode;
	t_cmplx		z;
	t_cmplx		c;
	t_cmplx		center;
	t_cmplx		cursor;
	t_cmplx		offset;
	double		plot_radius_x;
	double		plot_radius_y;
	double		lbound;
	double		rbound;
	double		tbound;
	double		bbound;
	double		bound;
	int			color;
	int			iter_rendition;
}	t_fractal;

// initiations.c
void	initialize_fields(t_fractal *fr, int argc, char **argv, int mode);
void	init_fractal(t_fractal *fr);
void	init_events(t_fractal *fr);

// renditions.c
void	render_fractals(void *f);
void	render_mandelbrot(t_fractal *fr);
void	render_julia(t_fractal *fr);
void	render_burning_ship(t_fractal *fr);

// complex_arithmetic.c
t_cmplx	c_sqr_plus_const(t_cmplx z, t_cmplx c);
t_cmplx	c_sqr_plus_const_abs(t_cmplx z, t_cmplx c);
double	c_dist_sqr(t_cmplx z);
double	ft_abs(double num);

// manage_events.c
void	upon_press(mlx_key_data_t keydata, void *param);
void	upon_scroll(double xdelta, double ydelta, void *param);
void	upon_close(void *param);
void	change_details(t_fractal *fr, mlx_key_data_t keydata);
void	change_color(t_fractal *fr);

// boundaries.c
void	update_geometry(t_fractal *fr);
void	move_fractal(t_fractal *fr, mlx_key_data_t keydata);
void	move_bounds(t_fractal *fr, mlx_key_data_t keydata);
void	ft_zoom(t_fractal *fr, double ydelta);
void	reset_bounds(t_fractal *fr);

// iterations.c
t_cmplx	get_next_iteration(t_cmplx z_n, t_cmplx c);
double	scale_p(double val, double max_val, double sc_min, double sc_max);
int		scale_color(int iter, int max_iter, t_fractal *fr);
int		blast_off(t_fractal *fr);

// utils.c
void	arg_error(int status);
double	ft_atod(char *str);
void	frexit(char *str, t_fractal *fr, int status);

#endif
