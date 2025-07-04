/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:19:51 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/04 18:18:57 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fr;
	int			mode;

	mode = 0;
	if (argc == 2 && ft_strncmp(argv[1], "Mandelbrot", 10) == 0)
		mode = 1;
	else if (argc == 4 && ft_strncmp(argv[1], "Julia", 5) == 0)
		mode = 2;
	else if (argc == 2 && ft_strncmp(argv[1], "Burning ship", 12) == 0)
		mode = 3;
	else
		arg_error(EXIT_FAILURE);
	initialize_fields(&fr, argc, argv, mode);
	init_fractal(&fr);
	init_events(&fr);
	mlx_loop(fr.mlx);
	mlx_terminate(fr.mlx);
	return (0);
}
