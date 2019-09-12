/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmpz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 13:06:29 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_jmpz(t_vm *vm, t_proc *process,
	t_param *params, t_op op)
{
	unsigned int	jmp_addr;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_ZJMP");
	jmp_addr = ((process->pc + ((short)params[0].val % IDX_MOD)) % MEM_SIZE);
	local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u)\n", "JMP_ADDR",
		jmp_addr, jmp_addr);
	if (process->carry == 1)
	{
		process->op_pc = jmp_addr;
		local_dbg(vm->options & OPTD, "Jumped at address %d\n", jmp_addr);
	}
	else
		local_dbg(vm->options & OPTD, "No carry me no jump\n");
}
