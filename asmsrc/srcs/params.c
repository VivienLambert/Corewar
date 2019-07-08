/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/08 15:52:39 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

int			ft_paramd(char **split, t_op *op, int size, t_gnl *gnl)
{
	unsigned int	param;

	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != DIRECT_CHAR)
	{
		ft_printf("%s is not a direct, did you mean %c%s ?\n", split[1],
				DIRECT_CHAR, split[1]);
		return (ft_errorparams(gnl, 0, split[1][0]));
	}
	param = ft_filllabel(op, split, 1);
	ft_fillparam1(op, size, DIR_CODE, param);
	return (1);
}

void		ft_paramrg(char **split, t_op *op)
{
	char			**reg;
	int				param;

	param = 0;
	reg = NULL;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[1], 'r',
				split[1]);
		return ;
	}
	if (!(reg = ft_strsplit(split[1], 'r')))
		return ;
	if (reg[0] && ((param = ft_atoi(reg[0])) <= 0 || param > REG_NUMBER))
	{
		ft_strdel(reg);
		ft_printf("Min register = 1 or Max registers = %i\n", REG_NUMBER);
		return ;
	}
	ft_fillparam1(op, 2, REG_CODE, param);
	ft_free_tab2d(&reg);
}

void		ft_paramld(char **split, t_op *op)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_idd(split, op, DIR_SIZE + 1, 1)))
		return ;
	if (split[2])
	{
		if (split[2][0] != 'r')
		{
			ft_printf("%s is not a register, did you mean %c%s ?\n", split[2],
				'r', split[2]);
			return ;
		}
		ft_fillrg(split, 2, op);
	}
}

void		ft_paramst(char **split, t_op *op)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1])
	{
		if (split[1] && split[1][0] != 'r')
		{
			ft_printf("%s is not a register, did you mean %c%s ?\n", split[1],
					'r', split[1]);
			return ;
		}
		ft_fillrg(split, 1, op);
	}
	if (!(ft_rgid(split, op, 2)))
		return ;
}

void		ft_param3rg(char **split, t_op *op)
{
	int		i;

	i = 0;
	if (split[0])
		ft_fillinstop(split[0], op);
	while (++i <= 3 && split[i])
	{
		if (split[i][0] != 'r')
		{
			ft_printf("%s is not a register, did you mean %c%s ?\n", split[i],
					'r', split[i]);
			return ;
		}
		ft_fillrg(split, i, op);
	}
}
