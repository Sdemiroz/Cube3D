/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:42:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/09 18:53:25 by pamatya          ###   ########.fr       */
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
# include <stdbool.h>
# include <unistd.h>

# define PI 3.141592654
# define HEIGHT 1080
# define WIDTH 1920
# define FOV 60.0f	// Field of View in degrees, f for float
# define MAP_H 200
# define MAP_W 200
# define START_PX 50
# define START_PY 50


# define READ_BUFFER 100
# define BLOCK_SIZE 20
# define MAP_OFFSET_X 50
# define MAP_OFFSET_Y 50

/******************************************************************************/
/********     COLORS     ******************************************************/
/******************************************************************************/

// Colors
# define BLACK       0x000000FF
# define WHITE       0xFFFFFFFF
# define RED         0xFF0000FF
# define GREEN       0x00FF00FF
# define BLUE        0x0000FFFF
# define YELLOW      0xFFFF00FF
# define CYAN        0x00FFFFFF
# define MAGENTA     0xFF00FFFF

// Gray Scale
# define GRAY        0x808080FF
# define LIGHT_GRAY  0xC0C0C0FF
# define DARK_GRAY   0x404040FF

// Common Game Colors
# define ORANGE      0xFF8000FF
# define PURPLE      0x8000FFFF
# define BROWN       0x8B4513FF
# define PINK        0xFF69B4FF

// Environment Colors
# define SKY_BLUE    0x87CEEBFF
# define FOREST_GREEN 0x228B22FF
# define STONE_GRAY  0x708090FF
# define SAND_YELLOW 0xF4A460FF

// Common Floor/Ceiling Colors
# define FLOOR_BROWN  0x8B4513FF
# define CEILING_BLUE 0x87CEEBFF
# define FLOOR_GRAY   0x696969FF
# define CEILING_WHITE 0xF5F5F5FF

// Minimap Colors
# define WALL_COLOR   0x000000FF  // Black walls
# define FLOOR_COLOR  0xFFFFFFFF  // White floor
# define PLAYER_COLOR 0xFF0000FF  // Red player dot
# define EMPTY_COLOR  0xC0C0C0FF  // Light gray for empty space

// Debug Colors
# define DEBUG_RED    0xFF000080  // Semi-transparent red
# define DEBUG_GREEN  0x00FF0080  // Semi-transparent green
# define DEBUG_BLUE   0x0000FF80  // Semi-transparent blue



typedef mlx_image_t		t_img;
typedef mlx_texture_t	t_txr;

typedef struct s_player
{
	int				start_x;
	int				start_y;
} t_player;

typedef struct s_map
{
	int			fd;
	int			height;
	int			width;
	t_img		*overview;
	t_player	*player;
} t_map;

typedef struct s_game
{
	mlx_t		*mlx;		// for window and mlx library
	t_img		*img_3d;	// for ray-casted 3D image to put on the window
	t_map		*map;		// pointer to map struct, also hold map image 
	t_player	*player;	// pionter to player struct for player position
	t_txr		*walls[4];	// for wall textures
} t_game;

/* ------------------------------- Functions ------------------------------- */

// spawn.c
t_game		*get_game(void);
t_map		*get_map(void);
t_player	*get_player(void);

// init_game.c
t_game		*init_game(t_game *game, char *input);

// start.c
void		game_start(t_game *game, char *path_to_map);

// renders.c
void		render_overview(t_game *game, char *path_to_map);

// events.c
void		init_events(t_game *game);

// error.c
void		exit_early(t_game *game, char *msg, int ret);

#endif
