/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:49:11 by casautou          #+#    #+#             */
/*   Updated: 2019/10/10 13:42:18 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*get_first_elem(t_stock *stock, t_wait *list)
{
	t_list *p;

	if (!(list))
		return (NULL);
	stock->io = list->io;
	p = list->point;
	stock->update = list->next;
	if (list)
		free(list);
	stock->free = stock->update;
	return (p);
}

t_wait	*add_list_next(t_wait *begin, t_wait *list, t_wait *box)
{
	if (!(list))
	{
		list = box;
		begin = list;
	}
	else
	{
		while (list->next)
			list = list->next;
		list->next = box;
	}
	return (begin);
}

t_wait	*add_list(t_stock *stock, t_list *elem, t_wait *list, int io)
{
	t_wait	*box;
	t_wait	*begin;

	if (!(box = (t_wait*)malloc(sizeof(t_wait))))
	{
		stock->malloc = 1;
		return (NULL);
	}
	box->point = elem;
	box->io = io;
	box->next = NULL;
	begin = list;
	return (add_list_next(begin, list, box));
}

int		get_flow(t_stock *stock, t_list *begin, t_paths *curr)
{
	t_wait	*list;
	int		test;

	list = NULL;
	init_get_flow(stock, begin);
	while (begin && begin->end != 1)
	{
		curr = begin->path;
		list = dispatch(stock, begin, curr, list);
		if (stock->malloc == 1)
			return (0);
		test = check_sat(stock, begin->nu, begin->nu) - 48;
		if (stock->io != test)
		{
			change_io(stock);
			list = dispatch(stock, begin, curr, list);
		}
		begin = get_first_elem(stock, list);
		list = stock->update;
	}
	if (begin && begin->end == 1)
		return (reverse_list(begin, stock));
	return (0);
}

int		karp(t_stock *stock, t_list *begin)
{
	t_paths	*curr;

	curr = NULL;
	init(stock, begin);
	if (stock->malloc == 1)
		return (error_msg(stock));
	while (begin->start != 1)
		begin = begin->next;
	if (direct_path(begin, stock) == 1)
		return (0);
	stock->ant = begin->ant_nb;
	while (get_flow(stock, begin, curr))
	{
		free_all(stock);
		apply_flow(stock);
		opti_path(stock, begin);
		if (stock->stop == 1)
				break ;
		apply_stock(stock);
	}
	free_all(stock);
	if (stock->flow == 0)
		return (error_msg(stock));
	get_in_line(stock, stock->real_begin);
	return (0);
}
