/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/06/18 05:24:47 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_game *game, char *msg, int ret)
{
	int	x;

	x = 0;
	if (msg)
		printf("%s", msg);
	if (!game)
		exit(ret);
	while (x != 5)
	{
		if (game->walls[x])
			mlx_delete_texture(game->walls[x]);
		x++;
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
	main_cleanup(ret);
}
