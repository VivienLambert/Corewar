/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/20 18:26:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_ld(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int load;
	unsigned int reg_dest;

	load = 0;
	reg_dest = 0;
	dbg_print_instruction_head(l_dbg, "OP_LD");
	load = read_parameter(vm, process, op, &params[0]);
	reg_dest = params[1].val;
	write_to_register(process, reg_dest, load);
	process_set_carry(process, op, load);
}

/*
** Unsure if address restriction has to be applied to param 1 if its type is IND
*/

void	op_ldi(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int reg_dest;
	unsigned int load_addr;
	unsigned int write;
	unsigned int src_1;
	unsigned int src_2;

	dbg_print_instruction_head(l_dbg, "OP_LDI");
	src_1 = read_parameter(vm, process, op, &params[0]);
	src_2 = read_parameter(vm, process, op, &params[1]);
	reg_dest = params[2].val;
	write = read_from_vm(vm, load_addr, sizeof(int));
	write_to_register(process, reg_dest, write);
	process_set_carry(process, op, write);
}
