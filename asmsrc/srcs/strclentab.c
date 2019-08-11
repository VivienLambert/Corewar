/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strclentab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:44:35 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/01 18:03:09 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static void	ft_noprint(const char *s1, char print, int *ret, int *occ)
{
	if (!print)
	{
		while (s1 && *s1)
		{
			if (*s1 == '\t')
				*ret += 8 - (*ret % 8);
			else
				(*ret)++;
			if (*s1 == SEPARATOR_CHAR)
				--(*occ);
			++s1;
			if (*occ == 0)
				break ;
		}
	}
}

static void	ft_loop(const char *s1, char print)
{
	int		i;
	int		j;

	while (*s1)
	{
		i = 0;
		j = 0;
		while (LABEL_CHARS[i])
		{
			if (LABEL_CHARS[i] == *s1)
				j = 1;
			if (j == 0)
				break ;
			i++;
		}
		ft_dprintf(2, "%c", print);
		if (j == 0)
			break ;
		++s1;
	}
}

static void	ft_ifprint(const char *s1, char print)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (*s1 && (*s1 == '\t' || *s1 == ' '))
	{
		if (*s1 == '\t')
		{
			k = 8 - (j % 8);
			j += k;
			while (k-- > 0)
				ft_dprintf(2, " ");
		}
		else
		{
			ft_dprintf(2, " ");
			j++;
		}
		i++;
		++s1;
	}
	ft_loop(s1, print);
}

int			ft_strclentab(const char *s1, char print, char *str, int occ)
{
	int	ret;

	ret = 0;
	if (!print)
		ft_noprint(s1, print, &ret, &occ);
	while (s1 && *s1 && s1 != str)
	{
		if (*s1 == '\t' && !print)
			ret += 8 - (ret % 8);
		else if (print)
			ft_ifprint(s1, print);
		else
			ret++;
		++s1;
	}
	if (ret)
		ret++;
	return (ret);
}
