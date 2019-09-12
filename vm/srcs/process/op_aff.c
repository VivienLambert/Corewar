/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:19:52 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 08:50:53 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_aff(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int reg_load;

	if (!(vm->options & OPTV))
		return ;
	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_AFF");
	if (read_from_register(process, params[0].val, &reg_load, vm))
		return ;
	reg_load %= 256;
	ft_printf("Player %d says : \"", process->player + 1);
	write(1, &reg_load, 1);
	ft_putstr("\"\n");
}
