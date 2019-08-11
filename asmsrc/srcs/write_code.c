/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:37:55 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/02 13:59:10 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int		accept_d4(int inst)
{
	if (inst == LIVE || inst == AND || inst == OR || inst == XOR || inst == LD
			|| inst == LLD)
		return (1);
	return (0);
}

int		has_no_ocp(int inst)
{
	return (inst == LIVE || inst == ZJMP || inst == FORK || inst == LFORK);
}

void	write_args(t_file *file, t_op *tmp, int i)
{
	unsigned int	to_write4;
	unsigned short	to_write2;
	unsigned char	to_write1;

	to_write4 = ft_reversebyte(tmp->param[i], 4);
	to_write2 = ft_reversebyte(tmp->param[i], 2);
	to_write1 = ft_reversebyte(tmp->param[i], 1);
	if (tmp->code[i] == REG_CODE)
		write(file->fdwrite, &to_write1, 1);
	else if ((tmp->code[i] == DIR_CODE || (has_no_ocp(tmp->inst) && i == 0))
			&& accept_d4(tmp->inst))
		write(file->fdwrite, &to_write4, 4);
	else if (tmp->code[i] || (has_no_ocp(tmp->inst) && i == 0))
		write(file->fdwrite, &to_write2, 2);
}

void	write_code(t_file *file, t_op *op)
{
	t_op			*tmp;
	int				i;
	char			opc;

	tmp = op;
	while (tmp)
	{
		if (tmp->inst != 0)
		{
			opc = 0;
			i = -1;
			write(file->fdwrite, &(tmp->inst), 1);
			if (tmp->inst != LIVE && tmp->inst != ZJMP && tmp->inst != FORK
					&& tmp->inst != LFORK)
			{
				opc = ft_opc(tmp->code);
				write(file->fdwrite, &opc, 1);
			}
			while (++i < 3)
				write_args(file, tmp, i);
		}
		tmp = tmp->next;
	}
}
