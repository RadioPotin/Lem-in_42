/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:48:42 by casautou          #+#    #+#             */
/*   Updated: 2019/09/14 15:48:43 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_matrix_next(t_stock *stock, int i, int k, int j)
{
	while (k < i)
	{
		j = 0;
		while (j < i)
		{
			stock->matrix[k][j] = '0';
			j++;
		}
		stock->matrix[k][j] = 0;
		k++;
	}
}

void	init_matrix(t_stock *stock, int i)
{
	int j;
	int k;

	j = 0;
	k = 0;
	stock->size = i;
	while (j < i)
	{
		if (!(stock->matrix[j] = (char*)malloc(sizeof(char) * (i + 1))))
		{
			stock->malloc = 1;
			return ;
		}
		j++;
	}
	init_matrix_next(stock, i, k, j);
}

void	init(t_stock *stock, t_list *begin)
{
	int i;

	i = 0;
	stock->ref = 1;
	stock->besturn = 2147483647;
	stock->real_begin = begin;
	while (begin)
	{
		begin->nu = i;
		begin = begin->next;
		i++;
	}
	if (!(stock->matrix = (char**)malloc(sizeof(char*) * (i + 1))))
	{
		stock->malloc = 1;
		return ;
	}
	init_matrix(stock, i);
}
