/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/10 20:11:06 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game = NULL;

	gc_init_garbage_collector();
	
	
	if (argc != 2)
		exit_early(game, "Error, Invalid Argument\n", 1);
    game = init_game(argv[1]);

	printf("Let the games begin!!!\n");
	game_start(game);
	init_events((void *)game);
	mlx_loop((*game).mlx);
	mlx_terminate((*game).mlx);
	gc_free_all();
    return(0);
}
