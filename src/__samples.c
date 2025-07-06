/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __samples.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 03:21:46 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/06 22:05:26 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ref_files/fractal_files_for_mlx_ref/fractol.h"

/*
MLX functions used in this file:
mlx_init		-	Initializes the MLX library and creates a new window.
		Syntax	:	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Fractal", 0);
		Note	:	WIDTH and HEIGHT are the dimensions of the window, and "Fractal" is the window title.
		
mlx_new_image	-	Creates a new image with specified dimensions.
		Syntax	:	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
		Note	:	mlx is the MLX context, WIDTH and HEIGHT are the dimensions of the image.
		
mlx_image_to_window	-	Displays the image in the specified window.
		Syntax	:	mlx_image_to_window(mlx, img, x, y);
		Note	:	x and y are the coordinates where the image will be displayed in the window.
		
mlx_loop		-	Starts the MLX event loop, which processes events and updates the window.
		Syntax	:	mlx_loop(mlx);
		NOte	:	This function blocks until the window is closed.

mlx_loop_hook	-	Sets a function to be called in each iteration of the MLX event loop.
		Syntax	:	mlx_loop_hook(mlx, &render_fractals, fr);
		Note	:	render_fractals is a function that will be called repeatedly to update the image.

mlx_scroll_hook	-	Sets a function to be called when the mouse wheel is scrolled.
		Syntax	:	mlx_scroll_hook(mlx, &upon_scroll, fr);
		Note	:	upon_scroll is a function that will handle the scroll events, and fr is a pointer to the fractal data.
		
mlx_key_hook	-	Sets a function to be called when a key is pressed.
		Syntax	:	mlx_key_hook(mlx, &upon_press, fr);
		Note	:	upon_press is a function that will handle key press events, and fr is a pointer to the fractal data.
		
mlx_close_hook	-	Sets a function to be called when the window is closed.
		Syntax	:	mlx_close_hook(mlx, &upon_close, fr);
		Note	:	upon_close is a function that will handle the window close event, and fr is a pointer to the fractal data.

mlx_get_mouse_pos-	Gets the current position of the mouse cursor.
		Syntax	:	mlx_get_mouse_pos(mlx, &cursor_x, &cursor_y);
		Note	:	cursor_x and cursor_y are pointers to integers where the mouse position will be stored.
		
mlx_put_pixel	-	Draws a pixel at the specified coordinates in the image.
		Syntax	:	mlx_put_pixel(img, x, y, color);
		Note	:	img is the image where the pixel will be drawn, x and y are the coordinates, and color is the color of the pixel.

mlx_delete_texture	-	Deletes a texture and frees its resources.
		Syntax	:	mlx_delete_texture(mlx_texture_t *texture);
		Note	:	This function should be called to free the memory allocated for the texture when it is no longer needed.
		*** It is important to call this function to avoid memory leaks.

mlx_terminate	-	Cleans up and terminates the MLX library.
		Syntax	:	mlx_terminate(mlx);
		Note	:	This function should be called before exiting the program to free resources.
		It is important to call it at the end of the program to clean up resources.

mlx_close_window	-	Closes the MLX window.
		Syntax	:	mlx_close_window(mlx);
		Note	:	This function closes the MLX window and frees associated resources.
		It is important to call this function before exiting the program to clean up resources.




(verify) mlx_put_texture	-	Draws a texture at the specified coordinates in the image.
		Syntax	:	mlx_put_texture(img, x, y, texture);
		Note	:	img is the image where the texture will be drawn, x and y are the coordinates, and texture is the texture to be drawn.
		*** This function is not used in the provided code, but it is available in MLX.
			This function can be used to draw textures onto images, similar to how pixels are drawn.
			A texture is a preloaded image that can be drawn onto another image at specified coordinates.

(verify) mlx_load_texture	-	Loads a texture from a file.
		Syntax	:	mlx_texture_t *texture = mlx_load_texture("path/to/texture.png");
		Note	:	This function loads a texture from the specified file path and returns a pointer to the texture.
		It is important to check if the texture was loaded successfully before using it.

(verify) mlx_put_texture_to_window	-	Draws a texture in the specified window.
		Syntax	:	mlx_put_texture_to_window(mlx, mlx_window_t *window, mlx_texture_t *texture, int x, int y);
		Note	:	This function draws the specified texture in the given window at the specified coordinates (x, y).
		It is important to ensure that the texture is valid before calling this function.
		
(verify) mlx_load_image	-	Loads an image from a file.
		Syntax	:	mlx_image_t *img = mlx_load_image(mlx, "path/to/image.png");
		Note	:	This function loads an image from the specified file path and returns a pointer to the image.
		It is important to check if the image was loaded successfully before using it.

(verify) mlx_load_png	-	Loads a PNG image from a file.
		Syntax	:	mlx_image_t *img = mlx_load_png(mlx, "path/to/image.png");
		Note	:	This function loads a PNG image from the specified file path and returns a pointer to the image.
		It is important to check if the image was loaded successfully before using it.
		
			
(verify) mlx_delete_image	-	Deletes an image and frees its resources.
		Syntax	:	mlx_delete_image(mlx, img);
		Note	:	This function should be called to free the memory allocated for the image when it is no longer needed.
		*** It is important to call this function to avoid memory leaks.

*/

/*
This file contains sample code snippets demonstrating the usage of MLX functions
MLX functions syntax examples.
mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Fractal", 0);
mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
mlx_image_to_window(mlx, img, 0, 0);
mlx_loop(mlx);
mlx_loop_hook(mlx, &render_fractals, fr);
mlx_scroll_hook(mlx, &upon_scroll, fr);
mlx_key_hook(mlx, &upon_press, fr);
mlx_close_hook(mlx, &upon_close, fr);
mlx_get_mouse_pos(mlx, &cursor_x, &cursor_y);
mlx_put_pixel(img, x, y, color);
mlx_terminate(mlx);

*/

// Sample for initiating mlx and mlx_image
void	init_fractal(t_fractal *fr)
{
	fr->mlx = mlx_init(WIDTH, HEIGHT, fr->name, 0);
	if (!fr->mlx)
		exit_early("Failed to initialize MLX", fr, EXIT_FAILURE);
	fr->img = mlx_new_image(fr->mlx, WIDTH, HEIGHT);
	if (!fr->img)
		exit_early("New image failed", fr, EXIT_FAILURE);
	render_fractals(fr);
	if (mlx_image_to_window(fr->mlx, fr->img, 0, 0) < 0)
		exit_early("Image to window failed", fr, EXIT_FAILURE);
}

// Sample for mlx event fns
void	init_events(t_fractal *fr)
{
	mlx_loop_hook(fr->mlx, &render_fractals, fr);
	mlx_scroll_hook(fr->mlx, &upon_scroll, fr);
	mlx_key_hook(fr->mlx, &upon_press, fr);
	mlx_close_hook(fr->mlx, &upon_close, fr);
}

// Sample for key press event
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

// Sample for key press events
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

// Sample for scroll event
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
	exit_early(NULL, fr, EXIT_SUCCESS);
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

// Sample for mlx_put_pixel for rendering pixels onto the image
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
// Sample for mlx termination and exit_early function
void	exit_early(char *str, t_fractal *fr, int status)
{
	if (str)
		perror(str);
	if (fr->mlx)
		mlx_terminate(fr->mlx);
	exit(status);
}
