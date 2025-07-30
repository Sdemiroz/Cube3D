/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_tabs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:47:35 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/30 01:50:19 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// char	*expand_tabs(char *line)
// {
// 	char	*expanded;
// 	int		x;
// 	int		y;
// 	int		tab_count;

// 	x = 0;
// 	tab_count = 0;
// 	while (line[x])
// 	{
// 		if (line[x] == '\t')
// 			tab_count++;
// 		x++;
// 	}
// 	if (tab_count == 0)
// 	{
// 		expanded = ft_strdup(line);
// 		free (line);
// 		return(expanded);
// 	}
// 	expanded = malloc((ft_strlen(line) + (tab_count * 3) + 1) * sizeof(char));
// 	if (!expanded)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	x = 0;
// 	y = 0;
// 	while (line[x])
// 	{
// 		if (line[x] == '\t')
// 		{
// 			expanded[y++] = ' ';
// 			expanded[y++] = ' ';
// 			expanded[y++] = ' ';
// 			expanded[y++] = ' ';
// 		}
// 		else
// 			expanded[y++] = line[x];
// 		x++;
// 	}
// 	expanded[y] = '\0';
// 	free(line);
// 	return (expanded);
// }

static int	count_tabs(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

static void	fill_expanded_line(char *expanded, char *line)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (line[x])
	{
		if (line[x] == '\t')
		{
			expanded[y++] = ' ';
			expanded[y++] = ' ';
			expanded[y++] = ' ';
			expanded[y++] = ' ';
		}
		else
			expanded[y++] = line[x];
		x++;
	}
	expanded[y] = '\0';
}

char	*expand_tabs(char *line)
{
	char	*expanded;
	int		tab_count;

	tab_count = count_tabs(line);
	if (tab_count == 0)
	{
		expanded = ft_strdup(line);
		free(line);
		return (expanded);
	}
	expanded = malloc((ft_strlen(line) + (tab_count * 3) + 1) * sizeof(char));
	if (!expanded)
	{
		free(line);
		return (NULL);
	}
	fill_expanded_line(expanded, line);
	free(line);
	return (expanded);
}
