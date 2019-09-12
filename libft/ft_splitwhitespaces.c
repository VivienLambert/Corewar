/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:04 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/29 15:06:52 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_words_l(char const *s)
{
	int i;

	i = 0;
	while (((s[i] < 9 || s[i] > 13) && s[i] != 32) && s[i] != '\0')
		i++;
	i++;
	return (i);
}

static int	ft_count_w(char const *s)
{
	int i;
	int count_word;
	int is_word;

	i = 0;
	count_word = 0;
	is_word = 0;
	while (s[i])
	{
		if (((s[i] < 9 || s[i] > 13) && s[i] != 32) && is_word == 0)
		{
			is_word = 1;
			count_word++;
		}
		else if ((((s[i] >= 9 && s[i] <= 13)) || s[i] == 32) && is_word == 1)
			is_word = 0;
		i++;
	}
	count_word++;
	return (count_word);
}

char		**ft_splitwhitespaces(char const *s)
{
	int		n;
	int		i;
	int		j;
	char	**tab;

	n = -1;
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * ft_count_w(s))))
		return (NULL);
	while (s[++n])
		if ((s[n] < 9 || s[n] > 13) && s[n] != 32)
		{
			if (!(tab[i] = (char*)malloc(sizeof(char) * ft_words_l(&s[n]))))
				return (NULL);
			while (((s[n] < 9 || s[n] > 13) && s[n] != 32) && s[n])
				tab[i][j++] = s[n++];
			tab[i++][j] = '\0';
			j = 0;
			n--;
		}
	tab[i] = NULL;
	return (tab);
}
