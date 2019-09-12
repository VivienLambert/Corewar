/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:49:39 by vlambert          #+#    #+#             */
/*   Updated: 2019/09/07 01:08:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	(*g_op_fptr[16])(t_vm*, t_proc*, t_param*, t_op) =
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
	&op_lfork,
	&op_aff
};

int		process_param_types(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	char	ocp;
	int		errors;

	ocp = 0;
	errors = 0;
	if (op.has_ocp)
	{
		local_dbg(vm->options & OPTD, "Getting types from OCP\n");
		ocp = read_byte_from_vm(vm, process->op_pc);
		local_dbg(vm->options & OPTD, "OCP = %x (%b)\n", ocp, ocp);
		process->op_pc += T_OCP;
		errors += set_params_from_ocp(params, op, ocp);
	}
	else
	{
		local_dbg(vm->options & OPTD, "Getting types from OP\n");
		set_params_from_op_info(params, op);
	}
	if (errors)
		local_dbg((vm->options & OPTD), "{red}OCP ERROR\n{eoc}");
	return (errors);
}

void	execute_instruction(t_vm *vm, t_proc *process, t_op op)
{
	t_param		params[4];
	int			errors;

	ft_bzero(params, sizeof(t_param) * 4);
	local_dbg(vm->options & OPTD, "{yellow}Instruction '%s' {eoc}\n",
		op.asm_name);
	errors = 0;
	process->op_pc = (process->pc + T_OPCODE);
	errors += process_param_types(vm, process, params, op);
	errors += get_op_parameters(vm, process, params, op);
	if (!errors)
		g_op_fptr[(int)(op.opcode - 1)](vm, process, params, op);
	process->pc = (process->op_pc) % MEM_SIZE;
	process->op_pc = process->pc;
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	if (process->waiting == -1 && (opcode <= 0 || opcode >= 17))
		process->pc = (process->pc + 1) % MEM_SIZE;
	else if (process->waiting == 0)
	{
		dbg_print_proc_head(vm->options & OPTD, vm, process);
		process->waiting = -1;
		execute_instruction(vm, process, g_op_tab[process->opcode - 1]);
		dbg_print_proc_end(vm->options & OPTD, vm, process);
	}
	else if (process->waiting == -1)
	{
		process->opcode = opcode;
		process->waiting = g_op_tab[opcode - 1].cycles - 2;
	}
	return (0);
}
