/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 12:20:31 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/02 13:14:56 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		assert_misplacement(t_parse *box, int i, char *mod)
{
	int j;

	while (box->input[i] && !*box->input[i])
		i++;
	if (!box->input[i] || ft_strchr(box->input[i], '-'))
		return (1);
	j = i + 1;
	while (box->input[j] && !ft_strchr(box->input[j], '-'))
	{
		if (!ft_strncmp(box->input[j], box->input[i],
					ft_strichr(box->input[i], ' ')))
			return (1);
		j++;
	}
	if (!assert_no_multiple_modifiers(box, i - 1, mod, j - 1))
		return (-1);
	return (0);
}

static int		assert_modifier(t_parse *box, int i, int *c)
{
	if (!ft_strcmp(START, box->input[i + 1])
			|| !ft_strcmp(END, box->input[i + 1])
			|| assert_misplacement(box, i + 1, box->input[i]))
		return (-1);
	*c += 1;
	return (0);
}

static int		find_start_and_end(t_parse *box)
{
	int i;
	int c;

	c = 0;
	i = 0;
	if (i < 0)
		return (0);
	while (box->input[i])
	{
		if (c == 2)
			return (1);
		if (!ft_strcmp(box->input[i], START)
				|| !ft_strcmp(box->input[i], END))
			if (assert_modifier(box, i, &c) == -1)
				break ;
		i++;
	}
	return (-1);
}

int				input_check(t_parse *box)
{
	int i;
	int com;

	i = 0;
	com = 0;
	while (box->input[i])
	{
		com += (*box->input[i] == '#'
				&& (ft_strcmp(box->input[i], START) != 0
					&& ft_strcmp(box->input[i], END) != 0)) ? 1 : 0;
		if (box->ants_i == -1 && ft_strisdigit(box->input[i])
				&& !ft_strchr(box->input[i], ' '))
			box->ants_i = i;
		else if (box->room_i == -1 && is_room(box->input[i]) == 1)
			box->room_i = i;
		else if (box->link_i == -1 && ft_strchr(box->input[i], '-'))
			box->link_i = i;
		i++;
	}
	if (com > 0)
		comment_clean(box, com);
	if (com < 0 || find_start_and_end(box) < 0)
		return (-1);
	return (0);
}
