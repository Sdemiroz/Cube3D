/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/05 22:44:33 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game = NULL;

	gc_init_garbage_collector();
	
	
	if (argc != 2)
		ft_error2(game, "Error, Invalid Argument\n", 1);
    game = init_game(game, argv[1]);

	printf("Let the games begin!!!\n");

	// mlx_loop((*game).mlx);
	// mlx_terminate((*game).mlx);
	gc_free_all();
    return(0);
}
