/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 21:27:19 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 16:20:01 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	process_set_carry(t_proc *process, t_op op, int value, t_vm *vm)
{
	if (!op.carry_flag)
		return ;
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
	if (vm->options & OPTD)
		local_dbg(vm->options & OPTD, "Value : %d, setting carry to %d\n",
			value, process->carry);
}
