/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:01:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/06/18 06:13:55 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	gc_init_garbage_collector();
	(void)argv;
	if (argc != 2)
		ft_error(game, "Error, Invalid Argument\n", 1);
    game = init_game(game, argv[1]);
	gc_free_all();
    return(0);
}
