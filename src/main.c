/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/01 06:34:09 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	gc_init_garbage_collector();
	if (argc != 2)
		exit_early(NULL, "Error, Invalid Argument\n", 1);
	ft_bzero(&game, sizeof(t_game));
	init_game_elements(&game, argv[1]);
	printf("Let the games begin!!!\n");
	game_start(&game);
	init_events((void *)&game);
	mlx_loop((game).mlx);
	mlx_terminate(game.mlx);

	gc_free_all();
    return(0);
}

