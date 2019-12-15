/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:13:38 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/03 15:30:31 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		comment_clean(t_parse *box, int com_nb)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (box->input[i] && c < com_nb)
	{
		if (*box->input[i] == '#'
				&& (ft_strcmp(box->input[i], START) != 0
					&& ft_strcmp(box->input[i], END) != 0))
		{
			ft_strclr(box->input[i]);
			c++;
		}
		i++;
	}
	return (0);
}

int		checknofeed(t_parse *box, int i)
{
	if (!i)
		return (1);
	else
	{
		while (i--)
		{
			if (*box->input[i])
			{
				if (box->verbose)
					box->verbose = 3;
				return (0);
			}
		}
	}
	return (1);
}

int		rot_hash(t_parse *box, char *room, size_t len)
{
	unsigned long	hash;
	size_t			i;

	i = 0;
	hash = 5381;
	while (i < len)
		hash = ((hash << 5) + hash) + room[i++];
	return (ft_abs(hash % box->room_nb));
}

void	ft_put_tab(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (*tab[i] == '\n')
		{
			ft_printf("%s", tab[i]);
			i++;
		}
		else
		{
			ft_printf("%s\n", tab[i]);
			i++;
		}
	}
}

int		is_room(char *line)
{
	if (ft_strcmp(START, line) == 0 || ft_strcmp(END, line) == 0)
		return (1);
	else if (ft_str_nb_of_target(line, " ") == 2
			&& ft_strisdigit(ft_strrchr(line, ' ') + 1)
			&& ft_strisdigit(ft_strchr(line, ' ') + 1)
			&& ft_count_word(line, ' ') == 3
			&& *line != 'L')
		return (1);
	else
		return (-1);
	return (-1);
}
