/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_interface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:59:21 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 01:00:49 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

void	gc_add_global(void *ptr)
{
	if (ptr)
		gc_add_to(&get_gc()->global, ptr);
}

void	gc_add_local(void *ptr)
{
	if (ptr)
		gc_add_to(&get_gc()->local, ptr);
}

void	gc_free_all(void)
{
	gc_free_gc(&get_gc()->local);
	gc_free_gc(&get_gc()->global);
}

void	gc_free_local(void)
{
	gc_free_gc(&get_gc()->local);
}

void	*ft_malloc(size_t size)
{
	return (ft_malloc_local(size));
}
