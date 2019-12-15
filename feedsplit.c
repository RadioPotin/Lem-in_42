/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_feedsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:05:07 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/02 13:05:40 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ft_countfeedword(char const *s, char c)
{
	int count;
	int nl;
	int i;

	count = 0;
	nl = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			nl += 1;
		else if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		i++;
	}
	return (count + nl);
}

static char	**fill_tab(char const *s, char c, char **tab)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
		{
			*tab[j] = s[i];
			j++;
			i++;
		}
		k = 0;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				tab[j][k++] = s[i++];
			i++;
			j++;
		}
	}
	return (tab);
}

static int	*count_lett(char const *s, char c, int size, int i)
{
	int		*lett;
	int		j;

	j = 0;
	if (!s || !(lett = (int *)ft_memalloc(sizeof(int) * size)))
		return (NULL);
	while (s[i] && j < size)
	{
		if (s[i] && s[i] == c)
		{
			lett[j++]++;
			i++;
		}
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
			{
				lett[j]++;
				i++;
			}
			i++;
			j++;
		}
	}
	return (lett);
}

char		**ft_feedsplit(char const *s, char c)
{
	char	**tab;
	int		words;
	int		*lett;
	int		i;

	words = 0;
	if (s != NULL)
		words = ft_countfeedword(s, c);
	if (!(lett = count_lett(s, c, words, 0))
			|| !(tab = (char **)ft_memalloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		if (!(tab[i] = ft_strnew(lett[i])))
		{
			ft_tabdel(i - 1, &tab);
			ft_memdel((void**)&lett);
			return (NULL);
		}
		i++;
	}
	tab[i] = 0;
	ft_memdel((void**)&lett);
	return (fill_tab(s, c, tab));
}
