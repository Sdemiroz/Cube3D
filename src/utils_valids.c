/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_valids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:48:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/13 02:51:47 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool is_valid(char c);
bool is_valid_block(char c);
bool is_player(char c);

bool is_valid(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool is_valid_block(char c)
{
	return (c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
