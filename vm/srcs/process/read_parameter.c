/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:15:43 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/31 16:24:18 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned int	read_parameter(t_vm *vm, t_proc *proc, t_op op, t_param *param)
{
	unsigned int	read;
	unsigned int	read_addr;

	read = 0;
	read_addr = 0;
	if (param->type == REG_CODE)
		read_from_register(proc, param->val, &read, vm);
	else if (param->type == IND_CODE)
	{
		if (op.addr_restrict)
			read_addr = (proc->pc + (short)((short)param->val % IDX_MOD))
				% MEM_SIZE;
		else
			read_addr = (proc->pc + param->val) % MEM_SIZE;
		read = read_from_vm(vm, read_addr, 4);
		dbg_print_ind_load(vm->options & OPTD, "IND_READ", read_addr, read);
	}
	else if (param->type == DIR_CODE)
	{
		read = op.dir_type ? (short)param->val : param->val;
		dbg_print_dir_load(vm->options & OPTD, "DIR_READ", read);
	}
	return (read);
}
