/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:14:59 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/23 19:35:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_add(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, t_op op)
{
	unsigned int op_result;
	unsigned int p1;
	unsigned int p2;

	dbg_print_instruction_head(l_dbg, "OP_ADD");
	p1 = read_parameter(vm, process, op, &params[0]);
	p2 = read_parameter(vm, process, op, &params[1]);
	op_result = (p1 + p2);
	dbg_print_math(l_dbg, '+', p1, p2, op_result);
	write_to_register(process, params[2].val, op_result);
	process_set_carry(process, op, op_result);
}
