/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:18:39 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 08:44:47 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

int		get_parameter(t_vm *vm, t_proc *proc, t_param *param, t_op op)
{
	if (param->type == DIR_CODE)
	{
		local_dbg(vm->options & OPTD, "%02x (DIR)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, op.dir_type == 0 ? 4 : 2);
		return (op.dir_type == 0 ? 4 : 2);
	}
	else if (param->type == IND_CODE)
	{
		local_dbg(vm->options & OPTD, "%02x (IND)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, IND_SIZE);
		return (IND_SIZE);
	}
	else if (param->type == REG_CODE)
	{
		local_dbg(vm->options & OPTD, "%02x (REG)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, T_REG);
		return (T_REG);
	}
	else
	{
		local_dbg(vm->options & OPTD, "{red}%02x (UNKNOWN){eoc}\n",
				param->type);
		return (0);
	}
}

int		bad_register(int register_id)
{
	return (register_id > REG_NUMBER || register_id < 1);
}

int		get_op_parameters(t_vm *vm, t_proc *proc, t_param *params, t_op op)
{
	int		i;
	int		parameter_size;
	int		errors;

	i = 0;
	errors = 0;
	parameter_size = 0;
	dbg_print_params_head(vm->options & OPTD);
	while (i < op.arg_nbr)
	{
		parameter_size = get_parameter(vm, proc, &params[i], op);
		errors += (parameter_size <= 0);
		errors += (params[i].type == REG_CODE && bad_register(params[i].val));
		proc->op_pc += parameter_size;
		local_dbg(vm->options & OPTD, "\n");
		i++;
	}
	return (errors);
}
