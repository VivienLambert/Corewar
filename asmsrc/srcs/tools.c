/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:40:25 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/06 16:30:01 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

int				ft_lentab2d(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char			ft_opc(int code[3])
{
	char	ret;
	int		i;

	ret = 0;
	i = 0;
	while (i < 3)
	{
		ret += code[i];
		ret = ret << 2;
		i++;
	}
	return (ret);
}

char			*ft_charwtspaces(char *str)
{
	int		i;
	int		len;
	char	*news;

	i = -1;
	len = 0;
	while (str[++i])
		if ((str[i] < 9 || str[i] > 13) && str[i] != 32)
			len++;
	if (!(news = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	news[len--] = '\0';
	while (--i >= 0)
		if ((str[i] < 9 || str[i] > 13) && str[i] != 32)
		{
			news[len--] = str[i];
		}
	return (news);
}

unsigned long	ft_atui(const char *str)
{
	unsigned long	res;
	int				i;
	int				neg;

	i = 0;
	res = 0;
	neg = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + ((str[i] - '0'));
		i++;
	}
	if (neg == 1)
		res = 4294967295 - (res - 1);
	return (res);
}
