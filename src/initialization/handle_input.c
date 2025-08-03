/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:19:54 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/08/01 06:19:33 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	assign_textures(t_game *game, mlx_texture_t **img, char *line,
// 			char *prefix);
void	assign_textures(t_game *game, t_txr **txr, char *line, char *prefix);

void	identify_rgb(t_game *game, char *line, t_color *color);
void	parse_line(t_game *game, char *line);
int		validate_map_line(t_game *game, char *line);

static int	parse_rgb(char *rgb_str, t_color *color);


int	validate_map_line(t_game *game, char *line)
{
	int	i;

	if (empty_line(line))
	{
		free(line);
		exit_early(game, "Error: Empty line in map", 1);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW", line[i]) && !ft_isspace(line[i]))
		{
			free(line);
			exit_early(game, "Error: Invalid character in map", 1);
		}
		if (line[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

// void	parse_line(t_game *game, char *line)
// {
// 	int	i;

// 	allocate_map_array(game, line);
// 	i = validate_map_line(game, line);
// 	game->map->map_array[game->data->tiles_y] = ft_strdup(line);
// 	if (!game->map->map_array[game->data->tiles_y])
// 	{
// 		free(line);
// 		exit_early(game, "Error allocating map line", 1);
// 	}
// 	gc_add_local(game->map->map_array[game->data->tiles_y]);
// 	if (i > game->data->tiles_x)
// 		game->data->tiles_x = i;
// 	game->data->tiles_y++;
// }

void	parse_line(t_game *game, char *line)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (trimmed)
		trimmed = expand_tabs(trimmed);
	if (!trimmed)
	{
		free(line);
		exit_early(game, "Error: trimming line", 1);
	}
	allocate_map_array(game, trimmed);
	i = validate_map_line(game, trimmed);
	game->map->map_array[game->data->tiles_y] = ft_strdup(trimmed);
	if (!game->map->map_array[game->data->tiles_y])
	{
		free(trimmed);
		exit_early(game, "Error allocating map line", 1);
	}
	gc_add_local(game->map->map_array[game->data->tiles_y]);
	if (i > game->data->tiles_x)
		game->data->tiles_x = i;
	game->data->tiles_y++;
	free(trimmed);
}


static int	parse_rgb(char *rgb_str, t_color *color)
{
	char	**parts;
	int		i;
	int		value;

	i = -1;
	parts = ft_split(rgb_str, ',');
	if (!parts)
		return (0);
	while (++i < 3)
	{
		value = ft_atoi(parts[i]);
		if (value < 0 || value > 255)
		{
			ft_free2d(parts);
			return (0);
		}
		if (i == 0)
			color->r = value;
		else if (i == 1)
			color->g = value;
		else
			color->b = value;
	}
	ft_free2d(parts);
	return (1);
}

void	identify_rgb(t_game *game, char *line, t_color *color)
{
	int		start;
	int		end;
	char	*rgb_str;

	end = 2;
	while (line[end] && ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && line[end] != '\n')
		end++;
	rgb_str = ft_calloc((end - start + 1), sizeof(char));
	if (!rgb_str)
	{
		free(line);
		exit_early(game, "Error allocating RGB string", 1);
	}
	ft_strlcpy(rgb_str, line + start, end - start + 1);

	if (!parse_rgb(rgb_str, color))
	{
		free(line);
		exit_early(game, "Error parsing RGB values", 1);
	}
	free(rgb_str);
}

// void	assign_textures(t_game *game, mlx_texture_t **img, char *line,
// 		char *prefix)
// {
// 	int		start;
// 	int		end;
// 	char	*texture_path;

// 	end = ft_strlen(prefix);
// 	while (line[end] && ft_isspace(line[end]))
// 		end++;
// 	start = end;
// 	while (line[end] && line[end] != '\n')
// 		end++;
// 	texture_path = ft_calloc(end - start + 1, sizeof(char));
// 	if (!texture_path)
// 	{
// 		free(line);
// 		exit_early(game, "Error, allocating texture path", 1);
// 	}
// 	ft_strlcpy(texture_path, line + start, end - start + 1);
// 	// *img = mlx_load_png(texture_path);
// 	// if (!(*img))
// 	// {
// 	// 	free(texture_path);
// 	// 	free(line);
// 	// 	exit_early(game, "Error loading texture", 1);
// 	// }
// 	free(texture_path);
// }

void	assign_textures(t_game *game, t_txr **txr, char *line, char *prefix)
{
	int		start;
	int		end;
	char	*texture_path;

	end = ft_strlen(prefix);
	while (line[end] && ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && line[end] != '\n')
		end++;
	texture_path = ft_calloc(end - start + 1, sizeof(char));
	if (!texture_path)
	{
		free(line);
		exit_early(game, "Error, allocating texture path", 1);
	}
	ft_strlcpy(texture_path, line + start, end - start + 1);
	*txr = mlx_load_png(texture_path);
	if (!(*txr))
	{
		free(texture_path);
		free(line);
		exit_early(game, "Error loading texture", 1);
	}

	free(texture_path);
}
