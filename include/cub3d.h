/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:42:58 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/24 21:08:17 by pamatya          ###   ########.fr       */
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
# include <math.h>

/******************************************************************************/
/********     COLORS     ******************************************************/
/******************************************************************************/

// Colors
# define BLACK			0x000000FF
# define WHITE			0xFFFFFFFF
# define RED			0xFF0000FF
# define GREEN			0x00FF00FF
# define BLUE			0x0000FFFF
# define YELLOW			0xFFFF00FF
# define CYAN			0x00FFFFFF
# define MAGENTA		0xFF00FFFF
# define RESET			0x00000000

// Gray Scale
# define GRAY			0x808080FF
# define LIGHT_GRAY		0xC0C0C0FF
# define DARK_GRAY		0x404040FF

// Common Game Colors
# define ORANGE			0xFF8000FF
# define PURPLE			0x8000FFFF
# define BROWN			0x8B4513FF
# define PINK			0xFF69B4FF

// Environment Colors
# define SKY_BLUE		0x87CEEBFF
# define FOREST_GREEN	0x228B22FF
# define STONE_GRAY		0x708090FF
# define SAND_YELLOW	0xF4A460FF

// Common Floor/Ceiling Colors
# define FLOOR_BROWN	0x8B4513FF
# define CEILING_BLUE	0x87CEEBFF
# define FLOOR_GRAY		0x696969FF
# define CEILING_WHITE	0xF5F5F5FF

// Minimap Colors
# define WALL_COLOR		0x000000FF  // Black walls
# define FLOOR_COLOR	0xFFFFFFFF  // White floor
# define PLAYER_COLOR	0xFF0000FF  // Red player dot
# define EMPTY_COLOR	0xC0C0C0FF  // Light gray for empty space

// Debug Colors
# define DEBUG_RED		0xFF000080  // Semi-transparent red
# define DEBUG_GREEN	0x00FF0080  // Semi-transparent green
# define DEBUG_BLUE		0x0000FF80  // Semi-transparent blue

/******************************************************************************/
/******     CONSTANTS     *****************************************************/
/******************************************************************************/

# define PI 3.141592654
# define READ_BUFFER 100

// Window Dimensions
# define WIDTH 1600
# define HEIGHT 900

// Player and Raycasting Constants
# define PLAYER_DIA 5
# define START_PX 100
# define START_PY 100
# define FOV 60.0f				// Field of View in degrees, f for float
# define NUM_RAYS 60

// Mini-Map Constants
# define TILE_SIZE 15
# define MAP_W 600
# define MAP_H 210
# define MAP_OFFSET_X 25
# define MAP_OFFSET_Y 25
# define MAP_SCALE 1.0f			// Scale for the minimap

/******************************************************************************/
/********     STRUCTS     *****************************************************/
/******************************************************************************/

typedef mlx_image_t		t_img;
typedef mlx_texture_t	t_txr;
typedef mlx_key_data_t	t_key;

typedef struct s_game t_game;
typedef struct s_data t_data;
typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_rays t_rays;
typedef struct s_game
{
	t_data		*data;			// for dynamic scaling and dimensioning
	mlx_t		*mlx;			// for window and mlx context
	t_img		*img3D;			// for ray-casted 3D image to be put on the window
	int32_t		img3D_inst_id;	// instance ID for 3D image
	
	// t_img		*gun3D;			// gun image to be used in 3D view
	// int32_t		gun_inst_id;	// gun instance ID for 3D image
	// t_txr		*walls[4];	// for wall textures
	
	t_map		*map;			// pointer to map struct, also holds map image
	t_player	*player;		// pointer to player struct for player position
	t_rays		*rays;
} t_game;

typedef struct s_data
{
	// Window Dimensions
	int		wind_w;
	int		wind_h;

	// Player elements
	int	 	pl_dia;
	int	 	pl_posx;
	int	 	pl_posy;

	// Ray casting elements
	float	fov;			// Field of View in degrees, f for float
	int		num_rays;		// No. of rays to cast within the FOV
	char	ini_dir;		// initial player direction character (N, S, E, W), initialized to N
	float	prev_dir;		// player direction in radians
	float	cur_dir;		// player direction in radians
	float	cosine;			// cos(cur_dir)
	float	sine;			// sin(cur_dir)
	
	// Mini-map elements
	int	 	mmp_w;
	int	 	mmp_h;
	int	 	mmp_offx;
	int	 	mmp_offy;
	int		mmp_scale;
	int	 	tile_size;		// size of each tile/block in the overview map
	int		tiles_x;
	int		tiles_y;
} t_data;

typedef struct s_map
{
	t_data		*data;
	t_img		*image;			// pointer to the image of the 2D map
	int			image_inst_id;	// instance ID for 2D map image
	int			fd;				// file descriptor for map file
	char		**map_array;	// 2D array of map data (strings)
	t_game		*game;
	t_player	*player;		// pointer to player struct for convenience
	t_rays		*rays;
} t_map;

typedef struct s_player
{
	t_data		*data;
	t_img		*blob2D;		// pointer to 2D player blob image
	int32_t		blob_inst_id;	// instance ID for 2D player blob	
	t_game		*game;
	t_map		*map;
	t_rays		*rays;
} t_player;

typedef struct s_rays
{
	t_data		*data;
	t_img		*rays;
	int			rays_inst_id;
	t_game		*game;
	t_map		*map;
	t_player	*player;
} t_rays;

/******************************************************************************/
/*******     FUNCTIONS     ****************************************************/
/******************************************************************************/

// // spawn.c

t_game		*get_game(void);
t_data		*get_data(void);
t_map		*get_map(void);
t_player	*get_player(void);
t_rays		*get_rays(void);

// init_game.c

void		init_game_elements(t_game *game, char *arg);

// start.c

void		game_start(t_game *game);

// draw.c

void		draw_map(t_game *game);
void	draw_player_direction(t_rays *rays, t_data *data);
void	erase_previous_ray(t_rays *rays, t_data *data);
void	draw_forward_ray(t_rays *rays, t_data *data);

// renders.c

void		render_map(void *param);

// events.c

void		init_events(void *param);

// error.c

void		exit_early(t_game *game, char *msg, int ret);

// utils_valids.c

bool 		is_valid(char c);
bool 		is_valid_block(char c);
bool 		is_player(char c);


// interims/circles_improved.c
void		place_player2D(t_game *game, int method);

// draw_circle.c
void		place_player2D_2(t_game *game, int method);



/******************************************************************************/
/*******    EXTRA FUNCTIONS     ***********************************************/
/******************************************************************************/

// src/temp_sources/parse_minimap.c

void		parse_minimap(t_map *map);

// src/temp_sources/print_map_utils.c

void		map_array_printer(t_map *map, int flag);

#endif
