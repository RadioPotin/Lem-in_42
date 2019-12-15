/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:42:33 by casautou          #+#    #+#             */
/*   Updated: 2019/09/25 17:42:38 by casautou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_malloc(t_stock *stock)
{
	if (!(stock->tab = (int*)malloc(sizeof(int) * (stock->flow + 1))))
	{
		stock->malloc = 1;
		return ;
	}
	if (!(stock->abp = (int*)malloc(sizeof(int) * (stock->flow + 1))))
	{
		stock->malloc = 1;
		return ;
	}
}
