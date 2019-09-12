/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:18:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 13:03:25 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_sub(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	op_result;
	unsigned int	p[2];

	dbg_print_instruction_head(vm->options & OPTD, "OP_SUB");
	p[0] = read_parameter(vm, process, op, &params[0]);
	p[1] = read_parameter(vm, process, op, &params[1]);
	op_result = (p[0] - p[1]);
	dbg_print_math(vm->options & OPTD, '-', p, op_result);
	if (write_to_register(process, params[2].val, op_result, vm) == 0)
		process_set_carry(process, op, op_result, vm);
}
