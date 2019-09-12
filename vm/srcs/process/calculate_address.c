/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:04:25 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/30 16:42:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned int	calculate_address(t_vm *vm, t_proc *proc, t_op op,
		unsigned int p[2])
{
	unsigned int	addr;

	if (op.addr_restrict)
		addr = ((int)proc->pc + (int)(p[0] + p[1]) % IDX_MOD);
	else
		addr = ((int)proc->pc + (int)(p[0] + p[1]));
	dbg_print_addr(vm->options & OPTD, op, proc, p);
	return (addr);
}
