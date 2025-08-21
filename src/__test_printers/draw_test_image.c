/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_test_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:19:31 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/13 15:29:59 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_test_image(void);

void	draw_test_image(void)
{
	t_map	*map;
	char	**img;
	int		i;
	int		j;

	map = get_map();
	img = map->img_array;
	
	j = -1;
	while (img[++j])
	{
		i = -1;
		while (img[j][++i])
		{
			if (img[j][i] == '1')
				mlx_put_pixel(map->test, i, j, TEST_IMG_RED);
		}
	}
}
