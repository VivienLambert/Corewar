/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillgeneric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:42:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:58:51 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static void	ft_fillinstop2(char *inst, t_op *tmp)
{
	if (!(ft_strcmp(inst, "st")))
		tmp->inst = ST;
	else if (!(ft_strcmp(inst, "add")))
		tmp->inst = ADD;
	else if (!(ft_strcmp(inst, "sub")))
		tmp->inst = SUB;
	else if (!(ft_strcmp(inst, "lld")))
		tmp->inst = LLD;
	else if (!(ft_strcmp(inst, "lldi")))
		tmp->inst = LLDI;
	else if (!(ft_strcmp(inst, "sti")))
		tmp->inst = STI;
	else if (!(ft_strcmp(inst, "and")))
		tmp->inst = AND;
	else if (!(ft_strcmp(inst, "or")))
		tmp->inst = OR;
	else if (!(ft_strcmp(inst, "xor")))
		tmp->inst = XOR;
	else if (!(ft_strcmp(inst, "aff")))
		tmp->inst = AFF;
}

void		ft_fillinstop(char *inst, t_op *op)
{
	t_op	*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	if (!(ft_strcmp(inst, "live")))
		tmp->inst = LIVE;
	else if (!(ft_strcmp(inst, "zjmp")))
		tmp->inst = ZJMP;
	else if (!(ft_strcmp(inst, "ldi")))
		tmp->inst = LDI;
	else if (!(ft_strcmp(inst, "fork")))
		tmp->inst = FORK;
	else if (!(ft_strcmp(inst, "lfork")))
		tmp->inst = LFORK;
	else if (!(ft_strcmp(inst, "ld")))
		tmp->inst = LD;
	else if (!(ft_strcmp(inst, "lld")))
		tmp->inst = LLD;
	else
		ft_fillinstop2(inst, tmp);
}

int			ft_filld(char **split, t_asm *tasm, int size)
{
	unsigned int	param;

	tasm->error = 0;
	if (ft_lentab2d(split) <= tasm->n_param)
	{
		tasm->error = 4;
		return (ft_syntax(NULL, tasm, ' '));
	}
	if (split[tasm->n_param] && split[tasm->n_param][0] == DIRECT_CHAR)
		param = ft_filllabel(tasm, split);
	if (tasm->error != 0)
		return (0);
	if (tasm->n_param == 1)
		ft_fillparam1(tasm, size, DIR_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, size, DIR_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, size, DIR_CODE, param);
	return (1);
}
