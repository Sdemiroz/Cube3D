/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:19:54 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 05:30:48 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parse_line(t_game *game, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]) || line[0] == '\n') // add check for i <= MAX WIDTH
		{
			free(line);
			exit_early(game, "Error: Invalid character or empty line in map", 1);
		}
		if (line[i] == '\n')
			break;
		i++;
	}
	game->map->map_array[game->map->height] = ft_strdup(line);
	gc_add_local(game->map->map_array[game->map->height]);
	if (!game->map->map_array[game->map->height])
	{
		free(line);
		exit_early(game, "Error allocating map line", 1);
	}
	if (i > game->map->width)
		game->map->width = i;
	game->map->height++;
}

static int	parse_rgb(char *rgb_str, t_color *color)
{
	char	**parts;
	int		i;
	int		value;

	i = 0;
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
	if(line[1] != ' ')	// maybe not mandatory to check, can be deletd for norminette
	{
		free(line);
		exit_early(game, "Error with Color Code", 1);
	}
	while (line[end] && ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && line[end] != '\n')
		end++;
	rgb_str = ft_malloc_global((end - start + 1) * sizeof(char));
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

void	assign_textures(t_game *game, mlx_texture_t **img, char *line, char *prefix)
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
	*img = mlx_load_png(texture_path);
	if (!(*img))
	{
		free(texture_path);
		free(line);
		exit_early(game, "Error loading texture", 1);
	}
	free(texture_path);
}
