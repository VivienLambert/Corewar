/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:27 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/22 23:15:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "vm.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_fork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int fork_addr;

	(void)op;
	dbg_print_instruction_head(l_dbg, "OP_FORK");
	fork_addr = (process->pc + (short)((short)params[0].val % IDX_MOD)) % MEM_SIZE;
	local_dbg(l_dbg, "%-15s: 0x%08x (%u)\n", "FORK_ADDR", fork_addr, fork_addr);
	add_process(vm, process->player, fork_addr, process);
}

void	op_lfork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int fork_addr;

	(void)op;
	dbg_print_instruction_head(l_dbg, "OP_LFORK");
	fork_addr = (process->pc + (short)((short)params[0].val)) % MEM_SIZE;
	local_dbg(l_dbg, "%-15s: 0x%08x (%u)\n", "FORK_ADDR", fork_addr, fork_addr);
	add_process(vm, process->player, fork_addr, process);
}
