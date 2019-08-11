/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:21:59 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/16 13:32:58 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_paramldi(char **split, t_asm *tasm)
{
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	tasm->n_param = 1;
	if (!(ft_rgidd(split, tasm, (DIR_SIZE / 2))))
		return (0);
	tasm->n_param = 2;
	if (!(ft_rgd(split, tasm, (DIR_SIZE / 2))))
		return (0);
	tasm->n_param = 3;
	if (split[3] && split[3][0] == 'r')
	{
		if (!(ft_fillrg(split, tasm)))
			return (0);
	}
	else
	{
		tasm->error = 1;
		return (ft_errorparams(tasm, split[3]));
	}
	return (1);
}

int		ft_paramsti(char **split, t_asm *tasm)
{
	tasm->n_param = 1;
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	if (split[1] && split[1][0] != 'r')
	{
		tasm->error = 1;
		return (ft_errorparams(tasm, split[1]));
	}
	if (!(ft_fillrg(split, tasm)))
		return (0);
	tasm->n_param = 2;
	if (!(ft_rgidd(split, tasm, (DIR_SIZE / 2))))
		return (0);
	tasm->n_param = 3;
	if (!(ft_rgd(split, tasm, (DIR_SIZE / 2))))
		return (0);
	return (1);
}

int		ft_paramcomp(char **split, t_asm *tasm)
{
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	tasm->n_param = 1;
	if (!(ft_rgidd(split, tasm, DIR_SIZE)))
		return (0);
	tasm->n_param = 2;
	if (!(ft_rgidd(split, tasm, DIR_SIZE)))
		return (0);
	tasm->n_param = 3;
	if (split[3] && split[3][0] != 'r')
	{
		tasm->error = 1;
		return (ft_errorparams(tasm, split[3]));
	}
	if (!(ft_fillrg(split, tasm)))
		return (0);
	return (1);
}
