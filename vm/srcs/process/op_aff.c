/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 16:19:52 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/09 14:43:16 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_aff(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int reg_load;

	if (!(vm->options & OPTV))
		return ;
	dbg_print_instruction_head(l_dbg, "OP_AFF");
	reg_load = read_from_register(process, params[0].val) % 256;
	ft_printf("Player %d says : \"", process->player + 1);
	write(1, &reg_load, 1);
	ft_putstr("\"\n");
}
