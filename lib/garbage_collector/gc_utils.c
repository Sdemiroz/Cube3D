/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:09:01 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 01:02:07 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

void	*ft_malloc_global(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	gc_add_global(ptr);
	return (ptr);
}

void	*ft_malloc_local(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	gc_add_local(ptr);
	return (ptr);
}

void	ft_error(char *msg, char *file, int line, uint8_t exit_stat)
{
	ft_fprintf(STDERR_FILENO, "Error: File %s line %d: %s\n", file, line, msg);
	main_cleanup(exit_stat);
}

void	main_cleanup(uint8_t exit_stat)
{
	gc_free_all();
	ft_bzero(get_gc(), sizeof(t_double_gc));
	exit(exit_stat);
}

void	gc_print_linked_list(t_garbage_collector *gc)
{
	if (!gc)
		return ;
	printf("Len of Linked List: %zu\n", gc->size);
	return ;
}



