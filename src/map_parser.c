/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:21:30 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/25 22:11:07 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		parse_game_data(t_game *game, char *map_name);

static void	check_file_type(t_game *game, char *map_name);
static void	read_and_parse_map(t_game *game);
static void	parse_key_data(t_game *game, char *line);
static int	get_key_index(char *line);


static int	get_key_index(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO_CHECK);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO_CHECK);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE_CHECK);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA_CHECK);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (F_CHECK);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (C_CHECK);
	return (-1);
}

static void	parse_key_data(t_game *game, char *line)
{
	static int checker[KEY_COUNT];
	int key;

	if (line[0] == '\n')
		return ;
	key = get_key_index(line);
	if (checker[key] || key == -1)
	{
		free(line);
		exit_early(game, "Error: Invalid identifier", 1);
	}
	checker[key] = 1;
	if (key == NO_CHECK)
		assign_textures(game, &(game->NO_texture), line, "NO");
	else if (key == SO_CHECK)
		assign_textures(game, &(game->SO_texture), line, "SO");
	else if (key == WE_CHECK)
		assign_textures(game, &(game->WE_texture), line, "WE");
	else if (key == EA_CHECK)
		assign_textures(game, &(game->EA_texture), line, "EA");
	else if (key == F_CHECK)
		identify_rgb(game, line, &(game->floor_color));
	else if (key == C_CHECK)
		identify_rgb(game, line, &(game->ceiling_color));
}


static void		read_and_parse_map(t_game *game)
{
	int		cur_state;
	char	*cur_line;

	cur_state = WAITING_FOR_MAP;
	cur_line = get_next_line(game->map->fd);
	if (!cur_line)
		exit_early(game, "Error, map empty", 1);
	while (cur_line)
	{
		if (cur_state == INITIAL_STATE)
		{
			parse_key_data(game, cur_line);
			if (check_key_data_completion(game))
					cur_state = WAITING_FOR_MAP;
		}
		else if (cur_state == WAITING_FOR_MAP && cur_line[0] == '\n')
			;
		else
		{
			cur_state = PARSING_MAP;
			parse_line(game, cur_line);
		}
		free(cur_line);
		cur_line = get_next_line(game->map->fd);
	}
}

// static void		read_and_parse_map(t_game *game)
// {
// 	int		cur_state;
// 	char	*cur_line;

// 	cur_state = INITIAL_STATE;
// 	cur_line = get_next_line(game->map->fd);
// 	if (!cur_line)
// 		exit_early(game, "Error, map empty", 1);
// 	while (cur_line)
// 	{
// 		if (cur_state == INITIAL_STATE)
// 		{
// 			parse_key_data(game, cur_line);
// 			if (check_key_data_completion(game))
// 					cur_state = WAITING_FOR_MAP;
// 		}
// 		else if (cur_state == WAITING_FOR_MAP && cur_line[0] == '\n')
// 			;
// 		else
// 		{
// 			cur_state = PARSING_MAP;
// 			parse_line(game, cur_line);
// 		}
// 		free(cur_line);
// 		cur_line = get_next_line(game->map->fd);
// 	}
// }

static void		check_file_type(t_game *game, char *map_name)
{
	char	*str;

	str = ft_strrchr(map_name, '.');
	if (!str)
		exit_early(game, "Error, invalid map name", 1);
	if (ft_strncmp(str, ".cub", 5) != 0)
		exit_early(game, "Error, invalid map name", 1);
}

void	parse_game_data(t_game *game, char *map_name)
{
	check_file_type(game, map_name);
	game->map->fd = open(map_name, O_RDONLY);
	if(!game->map->fd)
		exit_early(game, "Error opening file", 1);
	read_and_parse_map(game);
	int x;
	x = 0;
	while(game->map->map_array[x])
	{
		printf("%s\n", game->map->map_array[x]);
		x++;
	}
	printf("finished\n");
	gc_add_local(game->map->map_array);
	close(game->map->fd);
	pad_shorter_lines(game);
	check_map(game);
}
