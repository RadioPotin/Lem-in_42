/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casautou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:09:05 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/01 16:07:32 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		error_msg(t_stock *stock)
{
	if (stock->malloc == 1 && stock->verbose == 1)
		errout(stock->verbose, MALLOCER);
	else if (stock->verbose == 1)
		errout(stock->verbose, WAYERROR);
	else
		errout(stock->verbose, "");
	free_all(stock);
	return (0);
}
