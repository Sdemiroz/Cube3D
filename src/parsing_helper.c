/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:17:28 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/21 18:39:38 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_key_data_completion(t_game *game)
{
	if (game->NO_texture && game->SO_texture && game->WE_texture
		&& game->EA_texture)
		{
			if(game->ceiling_color.r && game->floor_color.r)
				return (1);
		}
	return (0);
}
