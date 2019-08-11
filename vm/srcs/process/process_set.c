/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 21:27:19 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/15 20:00:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

void	process_set_carry(t_proc *process, t_op op, int value)
{
	if (!op.carry_flag)
		return ;
	if (value == 0)
	{
		local_dbg(l_dbg, "Value : %d, setting carry to 1\n", value);
		process->carry = 1;
	}
	else
	{
		local_dbg(l_dbg, "Value : %d, setting carry to 0\n", value);
		process->carry = 0;
	}
}
