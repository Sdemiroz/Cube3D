/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/21 18:59:03 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	gc_init_garbage_collector();
	if (argc != 2)
		exit_early(game, "Error, Invalid Argument\n", 1);
	game = ft_malloc(sizeof(t_game));
	ft_bzero(game, sizeof(t_game));
	parse_game_data(game, argv[1]);
    game = init_game(argv[1]);
	printf("Let the games begin!!!\n");
	game_start(game);
	init_events((void *)game);
	mlx_loop((*game).mlx);
	mlx_terminate((*game).mlx);
	gc_free_all();
    return(0);
}
