/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:20:29 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 13:03:36 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_or(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int op_result;
	unsigned int src[2];

	ft_bzero(src, sizeof(int) * 2);
	dbg_print_instruction_head(vm->options & OPTD, "OP_OR");
	src[0] = read_parameter(vm, process, op, &params[0]);
	src[1] = read_parameter(vm, process, op, &params[1]);
	op_result = (src[0] | src[1]);
	dbg_print_math(vm->options & OPTD, '|', src, op_result);
	if (write_to_register(process, params[2].val, op_result, vm) == 0)
		process_set_carry(process, op, op_result, vm);
}
