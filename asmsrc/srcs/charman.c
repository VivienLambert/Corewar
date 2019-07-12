/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:05:37 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/12 13:55:41 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

int		ft_diffis(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (i);
}

int		ft_strclentab(const char *s1, char print, char *str, int occ)
{
	int	ret;
	int	j;

	ret = 0;
	while (s1 && *s1 && occ)
	{
		if (*s1 == '\t' || *s1 == ' ')
			ft_dprintf(2, "%c", *s1);
		if (*s1 == SEPARATOR_CHAR)
			--occ;
		else
			ret++;
		++s1;
	}
	while (s1 && *s1 && s1 != str)
	{
		if ((*s1 == '\t' || *s1 == ' '))
			ft_dprintf(2, "%c", *s1);
		else if (print)
		{
			j = -1;
			while (LABEL_CHARS[++j])
				if (LABEL_CHARS[j] == *s1)
					break ;
			if (LABEL_CHARS[j] != '\0')
				ft_dprintf(2, "%c", print);
		}
		else
			ret++;
		++s1;
	}
	ret++;
	return (ret);
}

void	ft_strprintspaces(const char *s1)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == ' ' || s1[i] == '\t')
			ft_dprintf(2, "%c", s1[i]);
		else
			break;
		i++;
	}
}
