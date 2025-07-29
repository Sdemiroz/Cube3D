/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 02:20:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/29 06:50:58 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	test_print_data();
void	test_print_rays(char c);


void	test_print_data()
{
	t_data	*data;

	data = get_data();
	printf("=============================================================\n");
	printf("Window Dimensions:\n");
	printf("window width:		wind_w		=	%d\n", data->wind_w);
	printf("window height:		wind_h		=	%d\n", data->wind_h);
	printf("\n");
	
	printf("Player elements:\n");
	printf("Player dia:		pl_dia		=	%d\n", data->pl_dia);
	printf("Player x:		pl_posx		=	%d\n", data->pl_posx);
	printf("Player dia:		pl_posy		=	%d\n", data->pl_posy);
	printf("\n");
	
	printf("Ray casting elements:\n");
	printf("Field of view:		fov		=	%.1f\n", data->fov);
	printf("Number of rays:		num_rays	=	%d\n", data->num_rays);
	printf("Initial direction:	ini_dir		=	%c\n", data->ini_dir);
	printf("Previous direction:	prev_dir	=	%.2f\n", data->prev_dir);
	printf("Current direction:	cur_dir		=	%.2f\n", data->cur_dir);
	printf("Cosine:			cosine		=	%.2f\n", data->cosine);
	printf("Sine:			sine		=	%.2f\n", data->sine);
	printf("\n");

	printf("Mini-map elements:\n");
	printf("Mini-map width:		mmp_w		=	%d\n", data->mmp_w);
	printf("Mini-map height:	mmp_h		=	%d\n", data->mmp_h);
	printf("Mini-map offset x:	mmp_offx	=	%d\n", data->mmp_offx);
	printf("Mini-map offset y:	mmp_offy	=	%d\n", data->mmp_offy);
	printf("Mini-map scale:		mmp_scale	=	%d\n", data->mmp_scale);
	printf("Tile size:		tile_size	=	%d\n", data->tile_size);
	printf("Tiles in x:		tiles_x		=	%d\n", data->tiles_x);
	printf("Tiles in y:		tiles_y		=	%d\n", data->tiles_y);
	printf("=============================================================\n");
	printf("\n");
}

void	test_print_rays(char c)
{
	t_rays	**rays;
	int		i;

	rays = get_player()->rays;
	printf("Rays:\n");
	i = -1;
	if (c == 'r')	// print angles in radians
	{
		while (rays[++i])
		{
			printf("Ray %d:\n", i);
			printf("  Delta: %.4f\n", rays[i]->delta);
			printf("  Angle: %.4f\n", rays[i]->angle);
			printf("  Cosine: %.4f\n", rays[i]->cosine);
			printf("  Sine: %.4f\n", rays[i]->sine);
			printf("  Length: %.4f\n", rays[i]->length);
			printf("  Hit X: %d\n", rays[i]->hit_x);
			printf("  Hit Y: %d\n", rays[i]->hit_y);
		}
	}
	else if (c == 'd') // print angles in degrees
	{
		while (rays[++i])
		{
			printf("Ray %d:\n", i);
			printf("  Delta: %.4f\n", rays[i]->delta * (180 / PI));
			printf("  Angle: %.4f\n", rays[i]->angle * (180 / PI));
			printf("  Cosine: %.4f\n", rays[i]->cosine);
			printf("  Sine: %.4f\n", rays[i]->sine);
			printf("  Length: %.4f\n", rays[i]->length);
			printf("  Hit X: %d\n", rays[i]->hit_x);
			printf("  Hit Y: %d\n", rays[i]->hit_y);
		}
	}
	else
		printf("Invalid argument for test_print_rays. Use 'r' for radians or 'd' for degrees.\n");
}
