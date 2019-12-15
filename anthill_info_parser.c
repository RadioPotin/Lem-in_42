/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill_info_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 12:32:11 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/04 13:49:23 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static long		quantity_of_ants(t_parse *box)
{
	int i;

	i = box->ants_i;
	if (i == -1 || !checknofeed(box, box->ants_i))
		return (0);
	if (ft_strisdigit(box->input[i]))
	{
		box->ant_nb = ft_atoll_base(box->input[i], "0123456789");
		ft_strclr(box->input[i++]);
	}
	while (i < box->room_i)
	{
		if (!*box->input[i])
			i++;
		else
		{
			if (box->verbose)
				box->verbose = 2;
			return (0);
		}
	}
	return (box->ant_nb);
}

static int		check_set(t_parse *box)
{
	int		ret1;
	long	ret2;

	ret1 = 0;
	ret2 = 0;
	box->link_i = -1;
	box->room_i = -1;
	box->ants_i = -1;
	if ((ret1 = input_check(box)) == -1
			|| (ret2 = quantity_of_ants(box)) <= 0
			|| ret2 > 2147483647 || room_description(box) == -1)
	{
		if (ret1 == -1)
			errout(box->verbose, MODERROR);
		else if (ret2 <= 0 || ret2 > 2147483647 || box->ants_i == -1)
			errout(box->verbose, ANTERROR);
		return (-1);
	}
	return (1);
}

static int		storer(int fd, t_parse *box)
{
	char *file;

	if ((file = get_full_file(fd))
			&& (box->input = ft_feedsplit(&file[1], '\n')))
	{
		if (!(box->output = ft_copy_tab(box->input)))
		{
			ft_tabdel(ft_tab_size(box->input), &box->input);
			errout(box->verbose, MEMERROR);
		}
		ft_strdel(&file);
		return (1);
	}
	else if (box->input == NULL && box->output)
		ft_strdel(&file);
	errout(box->verbose, MEMERROR);
	return (0);
}

void			printer(t_stock *box)
{
	ft_put_tab(box->output);
	ft_printf("\n");
}

t_list			*anthill_info_parser(int fd, t_parse *box, t_stock *stk)
{
	t_list *begin;

	begin = NULL;
	if (!storer(fd, box) || check_set(box) == -1
			|| !(begin = init_data_structure(box)))
	{
		free_parser(&box);
		return (NULL);
	}
	if (link_description(box, begin) == -1)
		return (NULL);
	stk->verbose = box->verbose;
	stk->output = ft_copy_tab(box->output);
	free_parser(&box);
	return (begin);
}
