/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:19:54 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/17 21:12:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	assign_textures(t_game *game, mlx_texture_t **img, char *line, char *prefix)
{
	size_t	prefix_len;
	int		i;
	int		start;
	char	*texture_path;

	prefix_len = ft_strlen(prefix);
	i = prefix_len;
	while (line[i] && ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	texture_path = ft_calloc(i - start + 1, sizeof(char));
	if (!texture_path)
	{
		free(line);
		exit_early(game, "Error, texture path missing", 1);
	}
	ft_strlcpy(texture_path, line + start, i - start + 1);
	*img = mlx_load_png(texture_path);
	if (!(*img))
	{
		printf("%s\n", texture_path);
		free(texture_path);
		free(line);
		exit_early(game, "Error loading texture", 1);
	}
	free(texture_path);
}

