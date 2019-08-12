/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:27 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 15:31:59 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "vm.h"

void	op_fork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int fork_addr;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_FORK");
	fork_addr = (process->pc + (short)((short)params[0].val % IDX_MOD))
		% MEM_SIZE;
	local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u)\n", "FORK_ADDR",
		fork_addr, fork_addr);
	add_process(vm, process->player, fork_addr, process);
}

void	op_lfork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int fork_addr;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LFORK");
	fork_addr = (process->pc + (short)((short)params[0].val)) % MEM_SIZE;
	local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u)\n", "FORK_ADDR",
		fork_addr, fork_addr);
	add_process(vm, process->player, fork_addr, process);
}
