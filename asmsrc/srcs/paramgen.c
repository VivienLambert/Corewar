/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramgen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:44:33 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 17:00:01 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static int	ft_iserr(t_asm *tasm)
{
	tasm->error = 4;
	return (ft_syntax(0, tasm, 0));
}

int			ft_idd(char **split, t_asm *tasm, int size)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == DIRECT_CHAR)
		{
			if (!(ft_filld(split, tasm, size)))
				return (0);
		}
		else if (split[tasm->n_param][0] == LABEL_CHAR ||
			(split[tasm->n_param][0] >= '0' &&
			split[tasm->n_param][0] <= '9') ||
			split[tasm->n_param][0] == '-' ||
			split[tasm->n_param][0] == '+')
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
		else
			return (ft_iserr(tasm));
	}
	else
		return (ft_iserr(tasm));
	return (1);
}

int			ft_rgd(char **split, t_asm *tasm, int size)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == 'r')
		{
			if (!(ft_fillrg(split, tasm)))
				return (0);
		}
		else if (split[tasm->n_param][0] == DIRECT_CHAR)
		{
			if (!(ft_filld(split, tasm, size)))
				return (0);
		}
		else
			return (ft_iserr(tasm));
	}
	else
		return (ft_iserr(tasm));
	return (1);
}

int			ft_rgidd(char **split, t_asm *tasm, int size)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == 'r')
		{
			if (!(ft_fillrg(split, tasm)))
				return (0);
		}
		else if (split[tasm->n_param][0] == DIRECT_CHAR)
			ft_filld(split, tasm, size);
		else
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
	}
	else
		return (ft_iserr(tasm));
	return (1);
}

int			ft_rgid(char **split, t_asm *tasm)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == 'r')
		{
			if (!(ft_fillrg(split, tasm)))
				return (0);
		}
		else if ((split[tasm->n_param][0] >= '0'
					&& split[tasm->n_param][0] <= '9')
				|| split[tasm->n_param][0] == '+'
				|| split[tasm->n_param][0] == '-'
				|| split[tasm->n_param][0] == LABEL_CHAR)
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
		else
			return (ft_iserr(tasm));
	}
	else
		return (ft_iserr(tasm));
	return (1);
}
