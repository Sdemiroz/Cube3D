/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 00:56:05 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/07/23 01:13:28 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

void	gc_add_to(t_garbage_collector *gc, void *ptr)
{
	t_gc_node	*new;

	new = gc_create_node(ptr);
	if (!new)
		ft_error("malloc fail", __FILE__, __LINE__, 1);
	new->next = gc->head;
	gc->head = new;
	gc->size++;
}

void	gc_free_gc(t_garbage_collector *gc)
{
	t_gc_node	*cur;
	t_gc_node	*tmp;

	if (!gc)
		return ;
	cur = gc->head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->pointer);
		free(cur);
		cur = tmp;
	}
	gc->head = NULL;
	gc->size = 0;
}

t_gc_node	*gc_create_node(void *pointer2mem)
{
	t_gc_node	*new_node;

	new_node = (t_gc_node *)malloc(sizeof(t_gc_node) * 1);
	if (!new_node)
		return (NULL);
	new_node->pointer = pointer2mem;
	new_node->next = NULL;
	return (new_node);
}

t_double_gc	*get_gc(void)
{
	static t_double_gc	dgc = {0};

	return (&dgc);
}

t_garbage_collector	*gc_init_garbage_collector(void)
{
	t_double_gc	*dgc;

	dgc = get_gc();
	dgc->global.head = NULL;
	dgc->global.tail = NULL;
	dgc->global.size = 0;
	dgc->local.head = NULL;
	dgc->local.tail = NULL;
	dgc->local.size = 0;
	return (&(dgc->global));
}


