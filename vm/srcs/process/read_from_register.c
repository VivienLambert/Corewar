/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:12:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/31 16:22:53 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

int	read_from_register(t_proc *proc, int id, unsigned int *read, t_vm *vm)
{
	if (id < 1 || id > REG_NUMBER)
	{
		local_dbg(vm->options & OPTD, "{red}REG_READ INVALID ID : '%d'{eoc}\n",
			id);
		return (1);
	}
	else
	{
		*read = proc->regs[id - 1];
		local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u) <- ", "REG_READ",
			*read, *read);
		local_dbg(vm->options & OPTD, "REG %d\n", id);
	}
	return (0);
}
