/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/11 21:28:10 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game			*init_game(char *arg);

static void		set_game_elements(t_game *game, char *path_to_map);

t_game	*init_game(char *arg)
{
	t_game	*game;
	
	game = get_game();
	if(!game)
		exit_early(game, "Malloc error Game\n", 1);
	set_game_elements(game, arg);

	// read_input(game);
	// parse_map(game);
	return (game);
}

static void	set_game_elements(t_game *game, char *path_to_map)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	game->img3D = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img3D)
		exit_early(game, "game_img3D: mlx_new_image", EXIT_FAILURE);
	
	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc", 1);
	game->map->image = mlx_new_image(game->mlx, MAP_W, MAP_H);
	if (!game->map->image)
		exit_early(game, "map_image: mlx_new_image", EXIT_FAILURE);
	game->map->fd = open(path_to_map, O_RDONLY);
	if (game->map->fd < 0)
		exit_early(game, path_to_map, EXIT_FAILURE);
	initialize_map2D(game, game->map);

		
	game->player = get_player();
	if (!game->player)
		exit_early(game, "game_player: malloc\n", 1);
	// game->player->blob2D = mlx_new_image(game->mlx, PLAYER_DIA + 2, PLAYER_DIA + 2);
	game->player->blob2D = mlx_new_image(game->mlx, 50, 50);
}

static void	initialize_map2D(t_game *game, t_map *map)
{
	char	**geometry;
	char	*next_line;
	int		i;
	int		j;

	geometry = ft_malloc(map->width * sizeof(char *) + 1);
	geometry[map->width] = NULL;
	i = -1;
	while (++i < map->width)
	{
		ft_malloc(map->height * sizeof(char) + 1);
		ft_memset(geometry[i], 32, map->height);	// filling up the whole string with spaces (' ' - ascii value 32)
		geometry[i][map->height] = 0;				// null termination at the end of each string
	}
	i = -1;
	next_line = get_next_line(map->fd);
	if (!next_line)
		exit_early(game, "gnl", EXIT_FAILURE);
	while (next_line || ++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			if (is_valid(next_line[j]))
				geometry[i][j] = next_line[j];
		}
		free(next_line);
		next_line = get_next_line(map->fd);
		if (!next_line)
			exit_early(game, "gnl", EXIT_FAILURE);
	}
	map->map_array = geometry;
}
