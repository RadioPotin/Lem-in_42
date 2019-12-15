/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 10:34:29 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/02 13:01:47 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	errout(int v, char *merr)
{
	if (!v)
		ft_printf("ERROR\n");
	else if (v == 1)
		ft_printf("%s\n", merr);
	else if (v == 2)
		errout(1, LINERROR);
	else if (v == 3)
		errout(1, PREERROR);
}
