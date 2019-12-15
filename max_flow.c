/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:09:59 by dapinto           #+#    #+#             */
/*   Updated: 2019/09/25 16:10:41 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	max_flow(t_stock *stock, t_list *begin)
{
	t_paths *a;

	stock->max = 0;
	a = begin->path;
	while (a)
	{
		stock->max++;
		a = a->next;
	}
	if (stock->ant < stock->max)
		stock->max = stock->ant;
	while (begin->nu != -1)
		begin = begin->next;
	a = begin->path;
	stock->max = 0;
	while (a)
	{
		stock->max++;
		a = a->next;
	}
	if (stock->ant < stock->max)
		stock->max = stock->ant;
}
