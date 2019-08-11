/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillparams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:25:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/22 17:47:36 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

void	ft_fillparam1(t_asm *tasm, int size, int code, unsigned int param1)
{
	t_op			*tmp;
	unsigned int	addr;

	tmp = tasm->op;
	addr = 0;
	while (tmp->next)
	{
		if (tmp->size != 0)
			addr += tmp->size;
		tmp = tmp->next;
	}
	tmp->param[0] = param1;
	tmp->addr = addr;
	if (tmp->inst)
	{
		if (tmp->inst != LIVE && tmp->inst != ZJMP && tmp->inst != FORK
				&& tmp->inst != LFORK)
			tmp->size = size + 2;
		else
			tmp->size = size + 1;
	}
	tmp->code[0] = code;
	tmp->line = tasm->gnl.nbline;
}

void	ft_fillparam2(t_op *op, int size, int code, unsigned int param2)
{
	t_op			*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	tmp->param[1] = param2;
	tmp->size += size;
	tmp->code[1] = code;
}

void	ft_fillparam3(t_op *op, int size, int code, unsigned int param3)
{
	t_op			*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	tmp->param[2] = param3;
	tmp->size += size;
	tmp->code[2] = code;
}
