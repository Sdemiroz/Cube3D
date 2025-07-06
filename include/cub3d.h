/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:42:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/06 03:14:11 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/includes/libft.h"
# include "../lib/includes/ft_printf.h"
# include "../lib/includes/get_next_line.h"
# include "../lib/includes/garbage_collector.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdio.h>

# define PI 3.141592654

typedef struct s_map
{
	int				height;
	int				width;
} t_map;

typedef struct s_player
{
	int				start_x;
	int				start_y;
} t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*map_img;
	mlx_image_t		*main_img;
	t_map			*map;
	t_player		*player;
	mlx_texture_t	*walls[4];
} t_game;


/* ------------------------------- Functions ------------------------------- */

// spawn.c
t_game		*get_game(void);
t_map		*get_map(void);
t_player	*get_player(void);

// init_game.c
t_game		*init_game(t_game *game, char *input);


// error.c
void		ft_error2(t_game *game, char *msg, int ret);

#endif
