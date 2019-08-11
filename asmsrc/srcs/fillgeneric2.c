/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillgeneric2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 09:43:21 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/07 15:58:50 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static int	ft_filli2(char **split, t_asm *tasm)
{
	int				i;
	int				isop;

	i = 0;
	isop = 0;
	while (split[tasm->n_param][i] >= '0' && split[tasm->n_param][i] <= '9')
	{
		if (split[tasm->n_param][i] == '+' || split[tasm->n_param][i] == '-'
				|| (split[tasm->n_param][i] >= '0'
					&& split[tasm->n_param][i] <= '9'))
			isop = 1;
		else if (((split[tasm->n_param][i] == '+' ||
						split[tasm->n_param][i] == '-') && isop == 1) ||
				split[tasm->n_param][i] < '0' || split[tasm->n_param][i] > '9')
		{
			tasm->error = 3;
			return (ft_syntax(NULL, tasm, split[tasm->n_param][i]));
		}
		i++;
	}
	return (1);
}

int			ft_filli(char **split, t_asm *tasm)
{
	unsigned int	param;

	param = 0;
	if (ft_lentab2d(split) <= tasm->n_param)
	{
		tasm->error = 4;
		return (ft_syntax(NULL, tasm, ' '));
	}
	if (split[tasm->n_param][0] == LABEL_CHAR)
		param = ft_filllabel(tasm, split);
	else if (!(ft_filli2(split, tasm)))
		return (0);
	if (split[tasm->n_param] && !param)
		param = ft_atui(split[tasm->n_param]);
	if (tasm->n_param == 1)
		ft_fillparam1(tasm, IND_SIZE, IND_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, IND_SIZE, IND_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, IND_SIZE, IND_CODE, param);
	return (1);
}

static int	ft_fillrg2(char **split, t_asm *tasm, char **reg)
{
	unsigned int		param;

	param = 0;
	if (reg[0])
	{
		if (((param = ft_atoi(reg[0])) <= 0) || param > REG_NUMBER)
		{
			ft_free_tab2d(&reg);
			tasm->error = 2;
			return (ft_errorparams(tasm, split[tasm->n_param]));
		}
	}
	else
	{
		tasm->error = 3;
		return (ft_syntax(NULL, tasm, split[0][0]));
	}
	if (tasm->n_param == 1)
		ft_fillparam1(tasm, 1, REG_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, 1, REG_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, 1, REG_CODE, param);
	ft_free_tab2d(&reg);
	return (1);
}

int			ft_fillrg(char **split, t_asm *tasm)
{
	char				**reg;
	int					i;

	reg = NULL;
	if (ft_lentab2d(split) <= tasm->n_param)
	{
		tasm->error = 4;
		return (ft_syntax(NULL, tasm, ' '));
	}
	if (split[tasm->n_param][0] != 'r')
		return (ft_syntax(NULL, tasm, split[tasm->n_param][0]));
	if (!(reg = ft_strsplit(split[tasm->n_param], 'r')))
		return (ft_free(NULL, 2, &tasm->gnl, NULL));
	if (split[tasm->n_param][0] == 'r')
	{
		i = 0;
		while (split[tasm->n_param][++i])
			if (split[tasm->n_param][i] < '0' || split[tasm->n_param][i] > '9')
			{
				tasm->error = 3;
				return (ft_syntax(NULL, tasm, split[tasm->n_param][i]));
			}
	}
	return (ft_fillrg2(split, tasm, reg));
}
