/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:19:54 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/18 16:28:47 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	rgb_str = ft_calloc(end - start + 1, sizeof(char));
	if (!rgb_str)
	{
		free(line);
		exit_early(game, "Error allocating RGB string", 1);
	}
	ft_strlcpy(rgb_str, line + start, end - start + 1);
	if (!parse_rgb(rgb_str, color))
	{
		free(rgb_str);
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
