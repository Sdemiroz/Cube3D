/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 05:48:45 by pamatya           #+#    #+#             */
/*   Updated: 2025/06/17 17:41:02 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	initialize_fields(t_fractal *fr, int argc, char **argv, int mode);
void	init_fractal(t_fractal *fr);
void	init_events(t_fractal *fr);

void	initialize_fields(t_fractal *fr, int argc, char **argv, int mode)
{
	fr->name = argv[1];
	fr->bound = ESC_RADIUS * ESC_RADIUS;
	fr->iter_rendition = MAX_ITER;
	fr->mode = mode;
	fr->center.rl = (GRAPH_XMAX + GRAPH_XMIN) / 2;
	fr->center.im = (GRAPH_YMAX + GRAPH_YMIN) / 2;
	fr->plot_radius_x = (GRAPH_XMAX - GRAPH_XMIN) / 2;
	fr->plot_radius_y = (GRAPH_YMAX - GRAPH_YMIN) / 2;
	fr->lbound = fr->center.rl - fr->plot_radius_x;
	fr->rbound = fr->center.rl + fr->plot_radius_x;
	fr->tbound = fr->center.im + fr->plot_radius_y * HEIGHT / WIDTH;
	fr->bbound = fr->center.im - fr->plot_radius_y * HEIGHT / WIDTH;
	if (mode == 2)
	{
		fr->c.rl = ft_atod(argv[2]);
		fr->c.im = ft_atod(argv[3]);
	}
	else
		(void)argc;
	fr->color = RED;
}

void	init_fractal(t_fractal *fr)
{
	fr->mlx = mlx_init(WIDTH, HEIGHT, fr->name, 0);
	if (!fr->mlx)
		frexit("Failed to initialize MLX", fr, EXIT_FAILURE);
	fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT);
	if (!fr->img)
		frexit("New image failed", fr, EXIT_FAILURE);
	render_fractals(fr);
	if (mlx_image_to_window(fr->mlx, fr->img, 0, 0) < 0)
		frexit("Image to window failed", fr, EXIT_FAILURE);
}

void	init_events(t_fractal *fr)
{
	mlx_loop_hook(fr->mlx, &render_fractals, fr);
	mlx_scroll_hook(fr->mlx, &upon_scroll, fr);
	mlx_key_hook(fr->mlx, &upon_press, fr);
	mlx_close_hook(fr->mlx, &upon_close, fr);
}
