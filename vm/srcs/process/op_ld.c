/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 13:05:19 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_ld(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int load;
	unsigned int reg_dest;

	load = 0;
	reg_dest = 0;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LD");
	load = read_parameter(vm, process, op, &params[0]);
	reg_dest = params[1].val;
	if (write_to_register(process, reg_dest, load, vm) == 0)
		process_set_carry(process, op, load, vm);
}

/*
** Unsure if address restriction has to be applied to param 1 if its type is IND
*/

void	op_ldi(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int reg_dest;
	unsigned int load_addr;
	unsigned int write;
	unsigned int src[2];

	dbg_print_instruction_head(vm->options & OPTD, "OP_LDI");
	src[0] = read_parameter(vm, process, op, &params[0]);
	src[1] = read_parameter(vm, process, op, &params[1]);
	reg_dest = params[2].val;
	load_addr = calculate_address(vm, process, op, src);
	write = read_from_vm(vm, load_addr, REG_SIZE);
	write_to_register(process, reg_dest, write, vm);
}
