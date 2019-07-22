/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/22 02:36:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_st(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int reg_load;

	(void)op;
	dbg_print_instruction_head(l_dbg, "OP_ST");
	reg_load = read_from_register(process, params[0].val);
	if (params[1].type == REG_CODE)
		write_to_register(process, params[1].val, params[0].val);
	else if (params[1].type == IND_CODE)
		write_to_vm(vm, process->pc + (params[1].val % IDX_MOD), reg_load, 4,
			process->player);
}

void	op_sti(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	store_addr;
	unsigned int	reg_load;
	unsigned int	p1;
	unsigned int	p2;

	dbg_print_instruction_head(l_dbg, "OP_STI");
	reg_load = read_from_register(process, params[0].val);
	p1 = read_parameter(vm, process, op, &params[1]);
	p2 = read_parameter(vm, process, op, &params[2]);
	store_addr = calculate_address(process, op, p1, p2);
	write_to_vm(vm, store_addr, reg_load, 4, process->player);
	process_set_carry(process, op, reg_load);
}
