/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:38:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/18 17:48:56 by bopopovi         ###   ########.fr       */

#include "proc.h"

static bool l_dbg = 1;

void	(*g_op_fptr[15])(t_vm*, t_proc*, t_param*, t_op) =
{
	&op_live,
	&op_ld,
	&op_st,
	&op_add,
	&op_sub,
	&op_and,
	&op_or,
	&op_xor,
	&op_jmpz,
	&op_ldi,
	&op_sti,
	&op_fork,
	&op_lld,
	&op_lldi,
	&op_lfork
};

int		process_param_types(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	char ocp;

	ocp = 0;
	if (op.has_ocp)
	{
		ocp = read_byte_from_vm(vm, process->op_pc);
		process->op_pc += T_OCP;
	}
	if (!op.has_ocp || ocp_match_instruction_params(op, ocp))
	{
		set_params(params, op, ocp);
		return (1);
	}
	return (0);
}

void	execute_instruction(t_vm *vm, t_proc *process, t_op op)
{
	t_param		params[3];

	local_dbg(l_dbg, "{yellow}Instruction '%s' (%#02x){eoc}\n", op.name, op.opcode);
	process->op_pc += T_OPCODE;
	if (process_param_types(vm, process, params, op))
	{
		if (get_op_parameters(vm, process, params, op) >= 0)
		{
			g_op_fptr[(int)(op.opcode - 1)](vm, process, params, op);
			process->pc = process->op_pc;
		}
		else
			process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else
		process->pc = (process->pc + 1) % MEM_SIZE;
	process->op_pc = process->pc;
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	local_dbg(l_dbg, "{green}[PROCESSING]{eoc}\n");
	local_dbg(l_dbg, "Player %d process %d\n", process->player, process->number);
	local_dbg(l_dbg, "CYCLE\t: %d\n", vm->cycles);
	local_dbg(l_dbg, "PC\t: %d\n", process->pc);
	if (opcode <= 0 || opcode >= 15)
	{
		local_dbg(l_dbg, "{red}Invalid opcode %#02hx{eoc}\n", opcode);
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
	else if (process->waiting == 0)
	{
		process->waiting = -1;
		process->op_pc = process->pc;
		execute_instruction(vm, process, g_op_tab[opcode - 1]);
	}
	else if (process->waiting == -1)
	{
		local_dbg(l_dbg, "OPCODE : %#02hx (%s)\n", opcode, g_op_tab[opcode - 1].name);
		local_dbg(l_dbg, "Set waiting to %d cycles\n", g_op_tab[opcode - 1].cycles);
		process->waiting = g_op_tab[opcode - 1].cycles;
	}
	local_dbg(l_dbg, "PC final state : %d\n", process->pc);
	local_dbg(l_dbg, "{green}[PROCESSING END]{eoc}\n\n");
	return (0);
}
